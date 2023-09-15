Imports System.Data.SqlClient
Imports System.Security.Cryptography

Public Class Cls_DatosLoraWan
    Class ClsEstado
        Public Dev_Eui As String
        Public Device_Id As String
        Public Application_Id As String
        Public IdUp As Long
        Public Frm_PayLoad_64 As String
        Public Frm_PayLoad_16 As String
        Public Contador As Integer
        Public CorrienteAnaloga0 As Integer
        Public CorrienteAnaloga1 As Integer
        Public Salida0 As Boolean
        Public Salida1 As Boolean
        Public Rele0 As Boolean
        Public Rele1 As Boolean

        Public Sub New()
            Dev_Eui = ""
            Device_Id = ""
            Application_Id = ""
            IdUp = -1
            Frm_PayLoad_64 = ""
            Frm_PayLoad_16 = ""
            Contador = 0
            CorrienteAnaloga0 = 0
            CorrienteAnaloga1 = 0
            Salida0 = 0
            Salida1 = 0
            Rele0 = 0
            Rele1 = 0
        End Sub
        Public Sub New(pDev_Eui As String, pDevice_Id As String, pApplication_Id As String, pIdUp As Long, pFrm_PayLoad_64 As String, pFrm_PayLoad_16 As String, pContador As Integer, pCorrienteAnaloga0 As Integer, pCorrienteAnaloga1 As Integer, pSalida0 As Boolean, pSalida1 As Boolean, pRele0 As Boolean, pRele1 As Boolean)
            Dev_Eui = pDev_Eui
            Device_Id = pDevice_Id
            Application_Id = pApplication_Id
            IdUp = pIdUp
            Frm_PayLoad_64 = pFrm_PayLoad_64
            Frm_PayLoad_16 = pFrm_PayLoad_16
            Contador = pContador
            CorrienteAnaloga0 = pCorrienteAnaloga0
            CorrienteAnaloga1 = pCorrienteAnaloga1
            Salida0 = pSalida0
            Salida1 = pSalida1
            Rele0 = pRele0
            Rele1 = pRele1
        End Sub

        Public Sub Copiar(pEstado As ClsEstado)
            Dev_Eui = pEstado.Dev_Eui
            Device_Id = pEstado.Device_Id
            Application_Id = pEstado.Application_Id
            IdUp = pEstado.IdUp
            Frm_PayLoad_64 = pEstado.Frm_PayLoad_64
            Frm_PayLoad_16 = pEstado.Frm_PayLoad_16
            Contador = pEstado.Contador
            CorrienteAnaloga0 = pEstado.CorrienteAnaloga0
            CorrienteAnaloga1 = pEstado.CorrienteAnaloga1
            Salida0 = pEstado.Salida0
            Salida1 = pEstado.Salida1
            Rele0 = pEstado.Rele0
            Rele1 = pEstado.Rele1
        End Sub
    End Class
    Class ClsLectura
        Public Fecha As DateTime
        Public Estado As ClsEstado
        Public IncrementoContador As Integer

        Public Sub New()
            Fecha = Now()
            IncrementoContador = 0
            Estado = New ClsEstado()
        End Sub

        Public Sub New(pFecha As DateTime, pIncremento As Integer, pEstado As ClsEstado)
            Fecha = pFecha
            IncrementoContador = pIncremento
            Estado = pEstado
        End Sub

        Public Sub Copiar(pFecha As DateTime, pIncremento As Integer, pEstado As ClsEstado)
            Fecha = pFecha
            IncrementoContador = pIncremento
            Estado.Copiar(pEstado)
        End Sub
    End Class

    Public colEstados As Collection
    Public datoRecibido As ClsLectura

    Public sAppId = "proyecto-elo308"

    Public Sub New()
        sQl += " and a.application_id='" + sAppId + "'"
        datoRecibido = New ClsLectura()
        colEstados = New Collection()
        Leer_Estados()
    End Sub

    Public Function Leer_Estados() As Boolean
        Dim conn As SqlConnection = New SqlConnection(PaBaseCasas.sConexion)
        Try
            conn.Open()
        Catch ex As Exception
            Desplegar_Estado(ex.Message)
            Return False
        End Try
        Dim comm As SqlCommand = conn.CreateCommand()
        comm.CommandType = CommandType.Text
        comm.CommandTimeout = PaBaseCasas.EsperaConexion
        comm.CommandText = "Select * From Estado_Dispositivos_Dragino_Lt_22222_M3 With (Nolock)"
        Dim rea As SqlDataReader = comm.ExecuteReader()
        While rea.Read()
            Dim oEstado As ClsEstado = New ClsEstado(rea("Dev_Eui").ToString().Trim(), rea("Device_Id").ToString().Trim(), rea("Application_Id").ToString().Trim(), rea("IdUp"), rea("Frm_Payload_64").ToString().Trim(), rea("Frm_Payload_16").ToString().Trim(), rea("Contador"), rea("CorrienteAnaloga0"), rea("CorrienteAnaloga1"), rea("Salida0"), rea("Salida1"), rea("Rele0"), rea("Rele1"))
            colEstados.Add(oEstado)
        End While
        conn.Close()
        Return True
    End Function

    Public Function Leer() As Boolean
        Dim conn As SqlConnection = New SqlConnection(PaBaseLoraWan.sConexion)
        Try
            conn.Open()
        Catch ex As Exception
            Desplegar_Estado(ex.Message)
            Return False
        End Try
        Dim bHay As Boolean = False
        Dim flagException = False
        Dim comm As SqlCommand = conn.CreateCommand()
        comm.CommandType = CommandType.Text
        comm.CommandTimeout = PaBaseLoraWan.EsperaComando
        comm.CommandText = sQl
        Dim rea As SqlDataReader = comm.ExecuteReader()
        Dim IdUpdate As Long = 0
        If rea.Read() Then
            Dim sFecha As String = rea("received_at").ToString().Trim()
            Dim fFecha As DateTime = DateTime.Parse(sFecha, Globalization.CultureInfo.InvariantCulture)
            Dim sDev_Eui As String = rea("dev_eui").ToString().Trim()
            Dim sDevice_Id As String = rea("device_id").ToString().Trim()
            Dim sApplication_Id As String = rea("application_id").ToString().Trim()
            Dim lIdUp As Long = rea("Id")
            IdUpdate = lIdUp
            Dim sFrm_Payload_64 As String = rea("frm_payload").ToString().Trim()
            Dim sFrm_Payload_16 As String = Frm64a16(sFrm_Payload_64)
            Dim regRecibido As ClsEstado = New ClsEstado(sDev_Eui, sDevice_Id, sApplication_Id, lIdUp, sFrm_Payload_64, sFrm_Payload_16, 0, 0, 0, False, False, False, False)
            If FormatearPayload(regRecibido) Then
                Dim iIncrementoContador As Integer = IncrementoContador(regRecibido)
                'Esto es Leido por Datos Condominio
                datoRecibido.Copiar(fFecha, iIncrementoContador, regRecibido)
                bHay = True
                Desplegar_Estado("Leyendo Fecha:" + sFecha + "Dev_Eui: " + sDev_Eui + " Incremento Contador: " + iIncrementoContador.ToString())
            Else
                flagException = True
            End If
        End If
        If flagException Then
            rea.Close()
            Dim comme As SqlCommand = conn.CreateCommand()
            comme.CommandType = CommandType.Text
            comme.CommandTimeout = PaBaseLoraWan.EsperaComando
            comme.CommandText = "Update UpLink Set Leido=1 Where id = " + IdUpdate.ToString()
            comme.ExecuteNonQuery()
            bHay = True
        End If
        conn.Close()
        Return bHay
    End Function

    Private Function MarcarComoLeidoLoraWan(pLectura As ClsLectura) As Boolean
        Dim conn As SqlConnection = New SqlConnection(PaBaseLoraWan.sConexion)
        Try
            conn.Open()
        Catch ex As Exception
            Desplegar_Estado(ex.Message)
            Return False
        End Try
        Dim bHay As Boolean = False
        Dim comm As SqlCommand = conn.CreateCommand()
        comm.CommandType = CommandType.Text
        comm.CommandTimeout = PaBaseLoraWan.EsperaComando
        Dim lId As Long = pLectura.Estado.IdUp
        comm.CommandText = "Update UpLink Set Leido=1 Where id = " + lId.ToString()
        comm.ExecuteNonQuery()
        conn.Close()
        Return True
    End Function

    'Ejecutada desde Datos Condominio
    Public Function Leido() As Boolean
        Desplegar_Estado("Marcando como Leido")
        If Not ActualizarEstado(datoRecibido.Estado) Then
            Return False
        End If
        If Not BdAgregarRecepcion(datoRecibido) Then
            Return False
        End If
        Return MarcarComoLeidoLoraWan(datoRecibido)
    End Function

    Private Function ActualizarEstado(pEstado As ClsEstado) As Boolean
        For Each Est As ClsEstado In colEstados
            If Est.Dev_Eui.CompareTo(pEstado.Dev_Eui) = 0 Then
                Est.Copiar(pEstado)
                Return BdActualizarEstado(Est)
            End If
        Next
        colEstados.Add(pEstado)
        Return BdAgregarEstado(pEstado)
    End Function

    Private Function BdActualizarEstado(pEstado As ClsEstado) As Boolean
        Dim conn As SqlConnection = New SqlConnection(PaBaseCasas.sConexion)
        Try
            conn.Open()
        Catch ex As Exception
            Desplegar_Estado(ex.Message)
            Return False
        End Try
        Dim comm As SqlCommand = conn.CreateCommand()
        comm.CommandType = CommandType.Text
        comm.CommandTimeout = PaBaseCasas.EsperaComando
        comm.CommandText = "Update Estado_Dispositivos_Dragino_Lt_22222_M3 Set "
        comm.CommandText += "IdUp = " + pEstado.IdUp.ToString() + ", "
        comm.CommandText += "Application_Id = '" + pEstado.Application_Id + "', "
        comm.CommandText += "Frm_Payload_64 = '" + pEstado.Frm_PayLoad_64 + "', "
        comm.CommandText += "Frm_Payload_16 = '" + pEstado.Frm_PayLoad_16 + "', "
        comm.CommandText += "Contador = " + pEstado.Contador.ToString() + ", "
        comm.CommandText += "CorrienteAnaloga0 = " + pEstado.CorrienteAnaloga0.ToString() + ", "
        comm.CommandText += "CorrienteAnaloga1 = " + pEstado.CorrienteAnaloga1.ToString() + ", "
        comm.CommandText += "Salida0 = " + IIf(pEstado.Salida0, "1", "0") + ", "
        comm.CommandText += "Salida1 = " + IIf(pEstado.Salida1, "1", "0") + ", "
        comm.CommandText += "Rele0 = " + IIf(pEstado.Rele0, "1", "0") + ", "
        comm.CommandText += "Rele1 = " + IIf(pEstado.Rele1, "1", "0") + " "
        comm.CommandText += "Where Dev_Eui = '" + pEstado.Dev_Eui + "'"
        Try
            comm.ExecuteNonQuery()
        Catch ex As Exception
            Desplegar_Estado(comm.CommandText)
            Desplegar_Estado(ex.Message)
            conn.Close()
            Return False
        End Try
        conn.Close()
        Return True
    End Function

    Private Function BdAgregarEstado(pEstado As ClsEstado) As Boolean
        Dim conn As SqlConnection = New SqlConnection(PaBaseCasas.sConexion)
        Try
            conn.Open()
        Catch ex As Exception
            Desplegar_Estado(ex.Message)
            Return False
        End Try
        Dim comm As SqlCommand = conn.CreateCommand()
        comm.CommandType = CommandType.Text
        comm.CommandTimeout = PaBaseCasas.EsperaComando
        comm.CommandText = "Insert Into Estado_Dispositivos_Dragino_Lt_22222_M3 "
        comm.CommandText += "(Dev_Eui, Device_Id, Application_Id, Frm_Payload_64, Frm_Payload_16, Contador, CorrienteAnaloga0, CorrienteAnaloga1, Salida0, Salida1, Rele0, Rele1, IdUp) "
        comm.CommandText += "Values ( "
        comm.CommandText += "'" + pEstado.Dev_Eui + "', '" + pEstado.Device_Id + "', '" + pEstado.Application_Id + "', '" + pEstado.Frm_PayLoad_64 + "', '" + pEstado.Frm_PayLoad_16 + "' "
        comm.CommandText += ", " + pEstado.Contador.ToString() + ", " + pEstado.CorrienteAnaloga0.ToString() + ", " + pEstado.CorrienteAnaloga1.ToString()
        comm.CommandText += ", " + IIf(pEstado.Salida0, "1", "0") + ", " + IIf(pEstado.Salida1, "1", "0")
        comm.CommandText += ", " + IIf(pEstado.Rele0, "1", "0") + ", " + IIf(pEstado.Rele1, "1", "0") + ", " + pEstado.IdUp.ToString()
        comm.CommandText += ")"
        Try
            comm.ExecuteNonQuery()
        Catch ex As Exception
            Desplegar_Estado(comm.CommandText)
            Desplegar_Estado(ex.Message)
            conn.Close()
            Return False
        End Try
        conn.Close()
        Return True
    End Function

    Private Function BdAgregarRecepcion(pLectura As ClsLectura) As Boolean
        Dim conn As SqlConnection = New SqlConnection(PaBaseCasas.sConexion)
        Try
            conn.Open()
        Catch ex As Exception
            Desplegar_Estado(ex.Message)
            Return False
        End Try
        Dim comm As SqlCommand = conn.CreateCommand()
        comm.CommandType = CommandType.Text
        comm.CommandTimeout = PaBaseCasas.EsperaComando
        comm.CommandText = "Insert Into Recepciones_Dispositivos_Dragino_Lt_22222_M3 "
        comm.CommandText += "(Dev_Eui, Device_Id, Application_Id, Frm_Payload_64, Frm_Payload_16, Contador, CorrienteAnaloga0, CorrienteAnaloga1, Salida0, Salida1, Rele0, Rele1, Fecha, Incremento_Contador) "
        comm.CommandText += "Values ( "
        comm.CommandText += "'" + pLectura.Estado.Dev_Eui + "', '" + pLectura.Estado.Device_Id + "', '" + pLectura.Estado.Application_Id + "', '" + pLectura.Estado.Frm_PayLoad_64 + "', '" + pLectura.Estado.Frm_PayLoad_16 + "' "
        comm.CommandText += ", " + pLectura.Estado.Contador.ToString() + ", " + pLectura.Estado.CorrienteAnaloga0.ToString() + ", " + pLectura.Estado.CorrienteAnaloga1.ToString()
        comm.CommandText += ", " + IIf(pLectura.Estado.Salida0, "1", "0") + ", " + IIf(pLectura.Estado.Salida1, "1", "0")
        comm.CommandText += ", " + IIf(pLectura.Estado.Rele0, "1", "0") + ", " + IIf(pLectura.Estado.Rele1, "1", "0")
        comm.CommandText += ", '" + pLectura.Fecha.ToString(Globalization.CultureInfo.InvariantCulture) + "'"
        comm.CommandText += ", " + pLectura.IncrementoContador.ToString()
        comm.CommandText += ")"
        Try
            comm.ExecuteNonQuery()
        Catch ex As Exception
            Desplegar_Estado(comm.CommandText)
            Desplegar_Estado(ex.Message)
            Desplegar_Estado(ex.HResult.ToString)
            conn.Close()
            If ex.HResult = -2146232060 Then
                Return True
            End If
            Return False
        End Try
        conn.Close()
        Return True
    End Function

    Private Function IncrementoContador(pRec As ClsEstado) As Integer
        Dim iInc As Integer = 0
        For Each Est As ClsEstado In colEstados
            If Est.Dev_Eui.CompareTo(pRec.Dev_Eui) = 0 Then
                iInc = pRec.Contador - Est.Contador
                If iInc < 0 Then
                    iInc = 0
                End If
                Return iInc
            End If
        Next
        Return iInc
    End Function

    Private Function Frm64a16(sPayload64 As String) As String
        Dim sPayload16 As String = ""
        Dim data As Byte() = Convert.FromBase64String(sPayload64)
        For Each i As Byte In data
            If i < 16 Then
                sPayload16 = sPayload16 + "0" + Conversion.Hex(i)
            Else
                sPayload16 = sPayload16 + Conversion.Hex(i)
            End If
        Next
        Return sPayload16
    End Function

    'Private Function FormatearPayload(ByRef registro As ClsEstado) As Boolean
    'Dim ValorHexadecimal = registro.Frm_PayLoad_16
    'Return True
    'Dim sPayload16 As String = ""
    'Dim data As Byte() = Convert.FromBase64String(sPayload64)
    'For Each i As Byte In data
    'sPayload16 = sPayload16 + Conversion.Hex(i)
    'Next
    'Return sPayload16
    'End Function

    Private Function FormatearPayload(ByRef pReg As ClsEstado) As Boolean
        Dim ValorHexadecimal As String = pReg.Frm_PayLoad_16
        If ValorHexadecimal.Length < 8 Then
            Return False
        End If
        Dim cuentahex As String = ValorHexadecimal.Substring(0, 8).Trim
        Dim dcuenta As Integer = Convert.ToInt32(cuentahex, 16)
        Dim corriente0hex As String = ValorHexadecimal.Substring(8, 4).Trim
        Dim corriente0 As Integer = Convert.ToInt32(corriente0hex, 16)
        Dim corriente1hex As String = ValorHexadecimal.Substring(12, 4).Trim
        Dim corriente1 As Integer = Convert.ToInt32(corriente1hex, 16)
        pReg.Contador = dcuenta
        pReg.CorrienteAnaloga0 = corriente0 'nA
        pReg.CorrienteAnaloga0 = corriente1
        Dim DIDOROS As String = ValorHexadecimal.Substring(16, 2).Trim
        Dim DIDORO As Byte = Convert.ToByte(DIDOROS, 16)
        pReg.Rele0 = DIDORO And &B1000_0000
        pReg.Rele1 = DIDORO And &B0100_0000
        pReg.Salida0 = DIDORO And &B0000_0001
        pReg.Salida1 = DIDORO And &B0000_0010
        Return True
    End Function

    Private sQl As String = <s>
        Select Top 1 
            up.Id, up.Leido, up.received_at, e.device_id, 
            e.dev_eui, e.join_eui, 
            e.dev_addr, a.application_id, 
            m.session_key_id, m.f_cnt, m.f_port, m.frm_payload, m.consumed_airtime, 
            s.data_rate_index, s.coding_rate, s.frequency, 
            r.bandwidth, r.spreading_factor
        From 
            UpLink up, UplinkMessage m, ApplicationIds a, DataRate d, EndDeviceIds e, Lora r, Settings s
        Where 
            up.uplink_messageid=m.Id and
            up.end_device_idsid=e.Id and 
            m.settingsId=s.Id and 
            e.application_idsid=a.Id and 
            s.data_rateId=d.Id and 
            d.loraId=r.Id and 
            up.Leido=0
        </s>

End Class
