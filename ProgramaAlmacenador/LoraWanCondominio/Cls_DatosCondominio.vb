Imports System.Data.SqlClient


Public Class Cls_DatosCondominio
    Private taProDra22222 As DataTable
    Private taMedidoresPulsoAgua As DataTable
    Private taValvulasDobleRele As DataTable
    Private taCondominio As DataTable

    Public PaBaseMedidores As Cls_ParametrosConexionBaseDato

    Public Sub New()
        taProDra22222 = New DataTable()
        taMedidoresPulsoAgua = New DataTable()
        taValvulasDobleRele = New DataTable()
        taCondominio = New DataTable()
        PaBaseMedidores = New Cls_ParametrosConexionBaseDato()
        PaBaseMedidores.LeerParametrosBase("Casas")
        PaBaseMedidores.sBase = "Medidores_Valvulas" 'sBase es una base de datos
        PaBaseMedidores.ArmarConexion()
        LlenarMedidoresPulsoAgua()
        LlenarValvulasDobleRele()
        LlenarTablaPropiedadesDispositivos()
        'LlenarCondominios()
    End Sub

    Private connCasas As SqlConnection
    Private commCasas As SqlCommand
    Private bAbierto As Boolean = False

    'Abre la conexion a la base de datos de las casas
    Public Function AbrirConexion() As Boolean
        If bAbierto Then
            Return True
        End If
        connCasas = New SqlConnection(PaBaseCasas.sConexion)
        Try
            connCasas.Open()
        Catch ex As Exception
            Desplegar_Estado(PaBaseCasas.sConexion)
            Desplegar_Estado(ex.Message)
            Return False
        End Try
        commCasas = connCasas.CreateCommand()
        commCasas.CommandType = CommandType.Text
        commCasas.CommandTimeout = PaBaseCasas.EsperaComando
        bAbierto = True
        Return True
    End Function

    'Cierra la conexion a la base de datos de las casas
    Public Function CerrarConexion() As Boolean
        If Not bAbierto Then
            Return True
        End If
        connCasas.Close()
        bAbierto = False
        Return True
    End Function

    'Inserta en detalles consumo casas valores atributos del dato leido, donde si
    'no exiten ningunas propiedades de dispositivos estas se agregan.
    Public Function Escribir(detLeido As Cls_DatosLoraWan.ClsLectura) As Boolean
        If Not bAbierto Then
            Desplegar_Estado("Se Debe Abrir Conexion a Base de Dato")
            Return False
        End If

        Dim drMedidor() As DataRow = taProDra22222.Select("Dev_Eui='" + detLeido.Estado.Dev_Eui + "'")
        If drMedidor.Length = 0 Then
            Desplegar_Estado("No Definidas Propiedades de Dispositivo " + detLeido.Estado.Dev_Eui)
            Desplegar_Estado("Se Agregará a Dispositivos con Valores por Defecto")
            AgregarDispositivo(detLeido.Estado.Dev_Eui, detLeido.Estado.Device_Id, detLeido.Estado.Application_Id)
            drMedidor = taProDra22222.Select("Dev_Eui='" + detLeido.Estado.Dev_Eui + "'")
        End If
        Dim lIdCasa As Long = drMedidor(0)("Id_Casa")
        Dim iUnidad As Int16 = drMedidor(0)("Unidad")
        Dim iPulsosUnidad As Decimal = drMedidor(0)("Pulsos_Unidad")
        Dim iCorrienteAbierta As Int16 = drMedidor(0)("Corriente_Abierta")
        Dim iCorrienteCerrada As Int16 = drMedidor(0)("Corriente_Cerrada")
        Dim dCantidad As Decimal = detLeido.IncrementoContador / (iPulsosUnidad * 60)
        Dim dCantidadAcumuladaAnterior As Decimal = UltimoDatoCantidadAcumulada(detLeido.Estado.Device_Id)
        Dim dCantidadAcumuladaNueva As Decimal = dCantidadAcumuladaAnterior + dCantidad
        Dim iCorriente As Int16 = detLeido.Estado.CorrienteAnaloga0
        Dim iApertura As Int16 = AperturaValvula(iCorrienteAbierta, iCorrienteCerrada, iCorriente)
        commCasas.CommandText = "Insert Into Detalles_Consumos_Casa (Fecha, Id_Casa, Tipo_Medicion, Unidad, Cantidad, AperturaValvula, Cantidad_Acumulada) "
        commCasas.CommandText += "Values ("
        commCasas.CommandText += "'" + detLeido.Fecha.ToString(Globalization.CultureInfo.InvariantCulture) + "'"
        commCasas.CommandText += ", " + lIdCasa.ToString() + ", 0, " + iUnidad.ToString()
        commCasas.CommandText += ", " + dCantidad.ToString("G", Globalization.CultureInfo.InvariantCulture)
        commCasas.CommandText += ", " + iApertura.ToString() + ", " + dCantidadAcumuladaNueva.ToString()
        commCasas.CommandText += ")"
        Try
            commCasas.ExecuteNonQuery()
        Catch ex As Exception
            Desplegar_Estado(commCasas.CommandText)
            Desplegar_Estado(ex.Message)
            If ex.HResult = -2146232060 Then
                Return True
            End If
            Return False
        End Try
        Desplegar_Estado("Agregado a Casa Consumo de " + dCantidad.ToString("n4", Globalization.CultureInfo.InvariantCulture) + " Litros")
        Return True
    End Function
    Private Function AperturaValvula(iCorrAbierta As Int16, iCorrCerrada As Int16, iCorriente As Int16) As Int16
        Dim iAper As Int16 = 100
        iAper = 100 - ((iCorriente - iCorrAbierta) / (iCorrCerrada - iCorrAbierta))
        Return iAper
    End Function

    Private Function UltimoDatoCantidadAcumulada(DeviceId As String) As Decimal
        Dim conn As SqlConnection = New SqlConnection(PaBaseCasas.sConexion)
        Try
            conn.Open()
        Catch ex As Exception
            Desplegar_Estado(PaBaseCasas.sConexion)
            Desplegar_Estado(ex.Message)
            Return False
        End Try
        Dim comm As SqlCommand = conn.CreateCommand()
        comm.CommandType = CommandType.Text
        comm.CommandTimeout = PaBaseCasas.EsperaConexion
        comm.CommandText = "  SELECT Top(1) Cantidad_Acumulada from Detalles_Consumos_Casa With(NoLock) "
        comm.CommandText += "where Id_Casa = (select Id_Casa from Propiedades_Dispositivos_Dragino_Lt_22222_M3 where Device_Id = '" + DeviceId + "') Order by Id Desc;"
        Dim rea As SqlDataReader
        Try
            rea = comm.ExecuteReader()
        Catch ex As Exception
            Desplegar_Estado(comm.CommandText)
            Desplegar_Estado(ex.Message)
            Return False
        End Try
        rea.Read()
        Dim lectura As String = rea("Cantidad_Acumulada").ToString().Trim() 'CDec(
        rea.Close()
        conn.Close()
        Return lectura
    End Function

    Private Function LlenarTablaPropiedadesDispositivos() As Boolean
        Dim conn As SqlConnection = New SqlConnection(PaBaseCasas.sConexion)
        Try
            conn.Open()
        Catch ex As Exception
            Desplegar_Estado(PaBaseCasas.sConexion)
            Desplegar_Estado(ex.Message)
            Return False
        End Try
        Dim comm As SqlCommand = conn.CreateCommand()
        comm.CommandType = CommandType.Text
        comm.CommandTimeout = PaBaseCasas.EsperaConexion
        comm.CommandText = "Select p.Dev_Eui, p.Id_Casa, m.Unidad, m.Pulsos_Unidad, v.Corriente_Abierta, v.Corriente_Cerrada "
        comm.CommandText += "From Propiedades_Dispositivos_Dragino_Lt_22222_M3 p With(Nolock), Medidores_Pulsos_Instalados m With(Nolock), Valvulas_Doble_Reles_Instaladas v With(NoLock) "
        comm.CommandText += "Where p.Id_Medidor_Instalado=m.Id_Medidor_Instalado And p.Id_Valvula_Rele_Instalada=v.Id_Valvula_Rele_Instalada And p.Funcion_Contador=1"
        Dim rea As SqlDataReader
        Try
            rea = comm.ExecuteReader()
        Catch ex As Exception
            Desplegar_Estado(comm.CommandText)
            Desplegar_Estado(ex.Message)
            Return False
        End Try
        taProDra22222.Clear()
        taProDra22222.Load(rea) 'Carga los en la tabla de propiedades temporal
        rea.Close()
        conn.Close()
        Return True
    End Function

    'Esta funcion verifica primero si exiten datos en la tabla Medidores_Pulso_Agua (mediante un comando SELECT),
    'donde en caso de no haber llena la tabla con valores por defecto (mediante un comando INSERT).
    Private Function LlenarMedidoresPulsoAgua() As Boolean
        Dim conn As SqlConnection = New SqlConnection(PaBaseMedidores.sConexion)
        Try
            conn.Open()
        Catch ex As Exception
            Desplegar_Estado(PaBaseCasas.sConexion)
            Desplegar_Estado(ex.Message)
            Return False
        End Try
        Dim comm As SqlCommand = conn.CreateCommand()
        comm.CommandType = CommandType.Text
        comm.CommandText = "Select * From Medidores_Pulso_Agua With(NoLock)"
        Dim rea As SqlDataReader = comm.ExecuteReader()
        taMedidoresPulsoAgua.Load(rea) 'Carga la tabla de datos temporal de los medidores de pulso de agua.
        rea.Close()
        If taMedidoresPulsoAgua.Rows.Count = 0 Then
            comm.CommandText = "Insert Into Medidores_Pulso_Agua (Marca, Modelo, Descripcion, Unidad, Pulsos_Unidad) "
            comm.CommandText += "Values ('Water Flow', 'YF-B5','Contador Flujo Agua DN20 1-30L/min', 0, 6.6)"
            comm.ExecuteNonQuery()
            comm.CommandText = "Select * From Medidores_Pulso_Agua"
            rea = comm.ExecuteReader()
            taMedidoresPulsoAgua.Load(rea)
            rea.Close()
        End If
        conn.Close()
        Return True
    End Function

    Private Function LlenarCondominios() As Boolean
        Dim conn As SqlConnection = New SqlConnection(PaBaseCasas.sConexion)
        Try
            conn.Open()
        Catch ex As Exception
            Desplegar_Estado(PaBaseCasas.sConexion)
            Desplegar_Estado(ex.Message)
            Return False
        End Try
        Dim comm As SqlCommand = conn.CreateCommand()
        comm.CommandType = CommandType.Text
        comm.CommandText = "DELETE From Condominio "
        'comm.ExecuteNonQuery()
        Dim rea As SqlDataReader = comm.ExecuteReader()
        rea.Close()
        comm.CommandText = "SELECT Distinct Application_Id From Propiedades_Dispositivos_Dragino_Lt_22222_M3 With(NoLock)"
        Dim reaa As SqlDataReader = comm.ExecuteReader()
        taCondominio.Load(reaa)
        'rea.Close()
        Dim aux As Integer = 1
        For index As Integer = 0 To taCondominio.Rows.Count - 1
            aux = aux + index
            comm.CommandText = "Insert Into Condominio (Id_Condominio, Descripcion, Application_Id) "
            comm.CommandText += "Values (" + aux.ToString() + ", 'Condominio1','" + taCondominio.Rows(index)("Application_Id").ToString().Trim() + "')"
            comm.ExecuteNonQuery()
            'comm.CommandText = "Select * From Condominio"
            'rea = comm.ExecuteReader()
            'taCondominio.Load(rea)
            'rea.Close()
        Next
        'rea.Close()
        conn.Close()
        Return True
    End Function

    'Esta funcion verifica primero si exiten datos en la tabla Valvulas_Doble_Rele (mediante un comando SELECT),
    'donde en caso de no haber llena la tabla con valores por defecto (mediante un comando INSERT).
    Private Function LlenarValvulasDobleRele() As Boolean
        Dim conn As SqlConnection = New SqlConnection(PaBaseMedidores.sConexion)
        Try
            conn.Open()
        Catch ex As Exception
            Desplegar_Estado(PaBaseCasas.sConexion)
            Desplegar_Estado(ex.Message)
            Return False
        End Try
        Dim comm As SqlCommand = conn.CreateCommand()
        comm.CommandType = CommandType.Text
        comm.CommandText = "Select * From Valvulas_Doble_Rele With(NoLock)"
        Dim rea As SqlDataReader = comm.ExecuteReader()
        taValvulasDobleRele.Load(rea)
        rea.Close()
        If taValvulasDobleRele.Rows.Count = 0 Then
            comm.CommandText = "Insert Into Valvulas_Doble_Rele (Marca, Modelo, Descripcion, Corriente_Abierta, Corriente_Cerrada, Tiempo_Abrir, Tiempo_Cerrar) "
            comm.CommandText += "Values ('Valvula', 'Agua 3/4', 'Valvula Agua 3/4 12V', 0, 10, 4, 4)"
            comm.ExecuteNonQuery()
            comm.CommandText = "Select * From Valvulas_Doble_Rele With(NoLock)"
            rea = comm.ExecuteReader()
            taValvulasDobleRele.Load(rea)
            rea.Close()
        End If
        conn.Close()
        Return True
    End Function

    'Agrega un dispositivo a la tabla Casas, donde Id_Casa aumenta automaticamente cada vez que se agrega una casa
    Private Function AgregarDispositivo(sDevEui As String, sDeviceId As String, sApplication_Id As String) As Boolean
        commCasas.CommandText = "Insert Into Casas (Descripcion, Eui_Agua) Values ('" + sDevEui + "', '" + sDevEui + "')"
        commCasas.ExecuteNonQuery()
        commCasas.CommandText = "Select Id_Casa From Casas With(NoLock) Where Eui_Agua = '" + sDevEui + "'"
        Dim rea As SqlDataReader = commCasas.ExecuteReader()
        rea.Read()
        Dim sIdCasa As String = rea("Id_Casa").ToString().Trim()
        rea.Close()

        Dim dPulsosUni As Decimal = taMedidoresPulsoAgua.Rows(0)("Pulsos_Unidad")
        commCasas.CommandText = "Insert Into Medidores_Pulsos_Instalados (Id_Medidor, Dev_Eui, Descripcion, Pulsos_Unidad) "
        commCasas.CommandText += "Values (" + taMedidoresPulsoAgua.Rows(0)("Id_Medidor").ToString()
        commCasas.CommandText += ", '" + sDevEui + "'"
        commCasas.CommandText += ", '" + taMedidoresPulsoAgua.Rows(0)("Descripcion").ToString().Trim() + "'"
        commCasas.CommandText += ", " + dPulsosUni.ToString("n4", Globalization.CultureInfo.InvariantCulture)
        commCasas.CommandText += ")"
        commCasas.ExecuteNonQuery()
        commCasas.CommandText = "Select Id_Medidor_Instalado From Medidores_Pulsos_Instalados With(NoLock) Where Dev_Eui = '" + sDevEui + "'"
        rea = commCasas.ExecuteReader()
        rea.Read()
        Dim sIdMedidorInst As String = rea("Id_Medidor_Instalado").ToString().Trim()
        rea.Close()

        commCasas.CommandText = "Insert Into Valvulas_Doble_Reles_Instaladas (Id_Valvula, Dev_Eui, Descripcion, Corriente_Abierta, Corriente_Cerrada, Tiempo_Abrir, Tiempo_Cerrar) "
        commCasas.CommandText += "Values (" + taValvulasDobleRele.Rows(0)("Id_Valvula").ToString()
        commCasas.CommandText += ", '" + sDevEui + "'"
        commCasas.CommandText += ", '" + taValvulasDobleRele.Rows(0)("Descripcion").ToString().Trim() + "'"
        commCasas.CommandText += ", " + taValvulasDobleRele.Rows(0)("Corriente_Abierta").ToString()
        commCasas.CommandText += ", " + taValvulasDobleRele.Rows(0)("Corriente_Cerrada").ToString()
        commCasas.CommandText += ", " + taValvulasDobleRele.Rows(0)("Tiempo_Abrir").ToString()
        commCasas.CommandText += ", " + taValvulasDobleRele.Rows(0)("Tiempo_Cerrar").ToString()
        commCasas.CommandText += ")"
        commCasas.ExecuteNonQuery()
        commCasas.CommandText = "Select Id_Valvula_Rele_Instalada From Valvulas_Doble_Reles_Instaladas With(NoLock) Where Dev_Eui = '" + sDevEui + "'"
        rea = commCasas.ExecuteReader()
        rea.Read()
        Dim sIdValvulaIns As String = rea("Id_Valvula_Rele_Instalada").ToString()
        rea.Close()

        commCasas.CommandText = "Insert Into Propiedades_Dispositivos_Dragino_Lt_22222_M3 (Dev_Eui, Device_Id, Descripcion, Id_Casa, Id_Medidor_Instalado, Id_Valvula_Rele_Instalada, Application_Id) "
        commCasas.CommandText += "Values('" + sDevEui + "', '" + sDeviceId + "', '" + sDevEui + "', " + sIdCasa
        commCasas.CommandText += ", " + sIdMedidorInst + ", " + sIdValvulaIns + ", " + sApplication_Id + ")"
        commCasas.ExecuteNonQuery()

        LlenarTablaPropiedadesDispositivos()
        Return True
    End Function

End Class
