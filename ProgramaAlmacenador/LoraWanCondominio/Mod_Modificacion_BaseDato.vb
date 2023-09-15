Imports System.Data.SqlClient

Module Mod_Modificacion_BaseDato
    Public Sub Agregar_Campo_AppId(oConn As Cls_ParametrosConexionBaseDato)
        Agregar_Campo_AppId(oConn, "Recepciones_Dispositivos_Dragino_Lt_22222_M3")
        Agregar_Campo_AppId(oConn, "Estado_Dispositivos_Dragino_Lt_22222_M3")
        Agregar_Campo_AppId(oConn, "Propiedades_Dispositivos_Dragino_Lt_22222_M3")
        Agregar_Campo_AppId(oConn, "Envios_Dispositivos_Dragino_Lt_22222")
        Agregar_Campo_AppId(oConn, "Condominio")
        Agregar_Campo_ConsumoAcumulado(oConn, "Detalles_Consumos_Casa")
        Agregar_Campo_IdUp(oConn, "Estado_Dispositivos_Dragino_Lt_22222_M3")
    End Sub




    Public Function Agregar_Campo_ConsumoAcumulado(oConn As Cls_ParametrosConexionBaseDato, sTabla As String) As Boolean
        If Not Existe_Tabla(oConn, sTabla) Then
            Return False
        End If
        Dim sQl As String = "Alter Table " + sTabla + " Add "
        Dim bModif As Boolean = False
        If Not Existe_Campo(oConn, sTabla, "Cantidad_Acumulada") Then
            sQl += "Cantidad_Acumulada Decimal(15,5) DEFAULT 0 NOT NULL"
            bModif = True
        End If
        If Not bModif Then
            Return True
        End If
        Desplegar_Estado(sQl)
        Dim conn As SqlConnection = New SqlConnection(oConn.sConexion)
        Try
            conn.Open()
        Catch ex As Exception
            Desplegar_Estado(oConn.sConexion)
            Desplegar_Estado(ex.Message)
            Return False
        End Try
        Dim comm As SqlCommand = conn.CreateCommand()
        comm.CommandType = CommandType.Text
        comm.CommandTimeout = oConn.EsperaComando
        comm.CommandText = sQl
        comm.ExecuteNonQuery()
        conn.Close()
        Return True
    End Function


    Public Function Agregar_Campo_AppId(oConn As Cls_ParametrosConexionBaseDato, sTabla As String) As Boolean
        If Not Existe_Tabla(oConn, sTabla) Then
            Return False
        End If
        Dim sQl As String = "Alter Table " + sTabla + " Add "
        Dim bModif As Boolean = False
        If Not Existe_Campo(oConn, sTabla, "Application_Id") Then
            sQl += "Application_Id VARCHAR(80) DEFAULT '' NOT NULL"
            bModif = True
        End If
        If Not bModif Then
            Return True
        End If
        Desplegar_Estado(sQl)
        Dim conn As SqlConnection = New SqlConnection(oConn.sConexion)
        Try
            conn.Open()
        Catch ex As Exception
            Desplegar_Estado(oConn.sConexion)
            Desplegar_Estado(ex.Message)
            Return False
        End Try
        Dim comm As SqlCommand = conn.CreateCommand()
        comm.CommandType = CommandType.Text
        comm.CommandTimeout = oConn.EsperaComando
        comm.CommandText = sQl
        comm.ExecuteNonQuery()
        conn.Close()
        Return True
    End Function

    Public Function Agregar_Campo_IdUp(oConn As Cls_ParametrosConexionBaseDato, sTabla As String) As Boolean
        If Not Existe_Tabla(oConn, sTabla) Then
            Return False
        End If
        Dim sQl As String = "Alter Table " + sTabla + " Add "
        Dim bModif As Boolean = False
        If Not Existe_Campo(oConn, sTabla, "IdUp") Then
            sQl += "IdUp BIGINT DEFAULT -1 NOT NULL"
            bModif = True
        End If
        If Not bModif Then
            Return True
        End If
        Desplegar_Estado(sQl)
        Dim conn As SqlConnection = New SqlConnection(oConn.sConexion)
        Try
            conn.Open()
        Catch ex As Exception
            Desplegar_Estado(oConn.sConexion)
            Desplegar_Estado(ex.Message)
            Return False
        End Try
        Dim comm As SqlCommand = conn.CreateCommand()
        comm.CommandType = CommandType.Text
        comm.CommandTimeout = oConn.EsperaComando
        comm.CommandText = sQl
        comm.ExecuteNonQuery()
        conn.Close()
        Return True
    End Function

    Public Function Existe_Tabla(oConn As Cls_ParametrosConexionBaseDato, sTablaDet As String) As Boolean
        Dim conn As SqlConnection = New SqlConnection(oConn.sConexion)
        Try
            conn.Open()
        Catch ex As Exception
            Desplegar_Estado(oConn.sConexion)
            Desplegar_Estado(ex.Message)
            Return False
        End Try
        Dim comm As SqlCommand = conn.CreateCommand()
        comm.CommandType = CommandType.Text
        comm.CommandTimeout = oConn.EsperaComando
        comm.CommandText = "Select table_name From INFORMATION_SCHEMA.Tables WITH(NOLOCK) Where TABLE_TYPE = 'BASE TABLE' And table_name = '" + sTablaDet + "'"
        Dim readExiste As SqlDataReader = comm.ExecuteReader()
        If Not readExiste.Read() Then
            readExiste.Close()
            conn.Close()
            Return False
        End If
        readExiste.Close()
        conn.Close()
        Return True
    End Function

    Public Function Existe_Campo(oConn As Cls_ParametrosConexionBaseDato, sTablaDet As String, sCampo As String) As Boolean
        Dim conn As SqlConnection = New SqlConnection(oConn.sConexion)
        Try
            conn.Open()
        Catch ex As Exception
            Desplegar_Estado(oConn.sConexion)
            Desplegar_Estado(ex.Message)
            Return False
        End Try
        Dim comm As SqlCommand = conn.CreateCommand()
        comm.CommandType = CommandType.Text
        comm.CommandTimeout = oConn.EsperaComando
        comm.CommandText = "SELECT table_name FROM information_schema.columns WITH(NOLOCK) WHERE table_name = '" + sTablaDet + "' and COLUMN_NAME = '" + sCampo + "'"
        Dim readExiste As SqlDataReader = comm.ExecuteReader()
        If Not readExiste.Read() Then
            readExiste.Close()
            conn.Close()
            Return False
        End If
        readExiste.Close()
        conn.Close()
        Return True
    End Function


End Module
