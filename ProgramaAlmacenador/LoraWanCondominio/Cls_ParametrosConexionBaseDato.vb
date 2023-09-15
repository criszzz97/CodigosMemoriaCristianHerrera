Public Class Cls_ParametrosConexionBaseDato
    Public sServidor As String = ""
    Public sBase As String = ""
    Public bSeguridadWindows As Boolean = False
    Public sUsuario As String = "sa"
    Public sClave As String = ""
    Public sConexion As String = ""
    Public EsperaConexion As Integer = 600
    Public EsperaComando As Integer = 600

    'Genera la conexion con la base de datos mediante la cadena de conexion especifica
    Public Function ArmarConexion() As String
        sConexion = "Data Source=" + sServidor + ";Initial Catalog=" + sBase + ";Persist Security Info=True;User ID=" + sUsuario + ";password=" + sClave + ";Pooling=false;Connection Timeout = " + EsperaConexion.ToString()
        If bSeguridadWindows Then
            sConexion = "Data Source=" + sServidor + ";Initial Catalog=" + sBase + ";Integrated Security=True;Pooling=false;Connection Timeout = " + EsperaConexion.ToString()
        End If
        Return sConexion
    End Function

    'Lee los parametros de una base de datos especifica, los cuales estan almacenados en el registro de windows sIdBase especifico
    Public Sub LeerParametrosBase(sIdBase As String)
        sServidor = GetSetting(sIdBase, "BD", "Servidor", "localhost")
        sUsuario = GetSetting(sIdBase, "BD", "Usuario", "sa")
        sClave = GetSetting(sIdBase, "BD", "Clave", "")
        Dim sSeguridadIntegrada = GetSetting(sIdBase, "BD", "Seguridad Integrada", "1")
        bSeguridadWindows = (sSeguridadIntegrada.CompareTo("1") = 0)
        Dim sEsperaConexion As String = GetSetting(sIdBase, "BD", "EsperaConexion", "600")
        sBase = GetSetting(sIdBase, "BD", "Base", "ProcesamientoConsumoAgua")
        Try
            EsperaConexion = Integer.Parse(sEsperaConexion) ' Setea el tiempo de timeout de espera de la conexion
        Catch ex As Exception
            Desplegar_Estado("EsperaConexion")
            Desplegar_Estado(ex.Message)
        End Try
        Dim sEsperaComando As String = GetSetting(sIdBase, "BD", "EsperaComando", "600")
        Try
            EsperaComando = Integer.Parse(sEsperaComando) ' Setea el tiempo de timeout de espera de una transaccion sql
        Catch ex As Exception
            Desplegar_Estado("EsperaComando")
            Desplegar_Estado(ex.Message)
        End Try
    End Sub

    'Escribe los parametros de una base de datos especifica en el registro de windows sIdBase
    Public Sub EscribirParametrosBase(sIdBase As String)
        SaveSetting(sIdBase, "BD", "Servidor", sServidor)
        SaveSetting(sIdBase, "BD", "Usuario", sUsuario)
        SaveSetting(sIdBase, "BD", "Clave", sClave)
        SaveSetting(sIdBase, "BD", "Base", sBase)
        SaveSetting(sIdBase, "BD", "Seguridad Integrada", IIf(bSeguridadWindows, "1", "0"))
        SaveSetting(sIdBase, "BD", "EsperaConexion", EsperaConexion.ToString())
        SaveSetting(sIdBase, "BD", "EsperaComando", EsperaComando.ToString())
    End Sub

End Class
