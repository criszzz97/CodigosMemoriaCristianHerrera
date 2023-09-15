Module Mod_LoraWanCondominio
    Public PaBaseLoraWan As Cls_ParametrosConexionBaseDato
    Public PaBaseCasas As Cls_ParametrosConexionBaseDato
    Public DatosLoraWan As Cls_DatosLoraWan
    Public DatosCondominio As Cls_DatosCondominio

    Private bIniciado As Boolean = False

    'Esta funcion se llama cuando se carga el programa al inicio.
    Public Sub Iniciar()
        PaBaseCasas = New Cls_ParametrosConexionBaseDato()
        PaBaseLoraWan = New Cls_ParametrosConexionBaseDato()
        LeerParametrosBaseCasas() 'Setea los parametros por defecto de la base de Casas.
        LeerParametrosBaseLoraWan() 'Setea los parametros por defecto de la base de Lorawan.
        Agregar_Campo_AppId(PaBaseCasas)
        DatosLoraWan = New Cls_DatosLoraWan()
        DatosCondominio = New Cls_DatosCondominio
        bIniciado = True
    End Sub

    'Esta funcion lee los parametros por defecto de la base Lorawan, esto ocurre cuando se llama a la funcion iniciar
    'al comenzar el programa, la cual asigna los parametros en los atributos de conexion de la base de datos PaBaseLoraWan,
    'para luego en base a esos atributos armar la conexion inicial.
    Public Sub LeerParametrosBaseLoraWan()
        PaBaseLoraWan.LeerParametrosBase("LoraWan") 'Lee los parametros del registro LoraWan
        PaBaseLoraWan.ArmarConexion()
    End Sub

    'Esta funcion guarda los valores de los parametros de configuracion de la base de datos
    'PaBaseLoraWan en el registro de windows Lorawan
    Public Sub EscribirParametrosBaseLoraWan()
        PaBaseLoraWan.EscribirParametrosBase("LoraWan")
    End Sub

    'Esta funcion lee los parametros por defecto de la base Casas, esto ocurre cuando se llama a la funcion iniciar
    'al comenzar el programa, la cual asigna los parametros en los atributos de conexion de la base de datos PaBaseCasas,
    'para luego en base a esos atributos armar la conexion inicial.
    Public Sub LeerParametrosBaseCasas()
        PaBaseCasas.LeerParametrosBase("Casas") 'Lee los parametros del registro Casas
        PaBaseCasas.ArmarConexion()
    End Sub

    'Esta funcion guarda los valores de los parametros de configuracion de la base de datos
    'PaBaseCasas en el registro de windows Casas
    Public Sub EscribirParametrosBaseCasas()
        PaBaseCasas.EscribirParametrosBase("Casas")
    End Sub

    Private bOcupado As Boolean = False

    Public Sub TimerProcesamiento()
        If Not bIniciado Then
            Return
        End If
        If bOcupado Then
            Return
        End If
        bOcupado = True
        If Not DatosCondominio.AbrirConexion() Then
            Desplegar_Estado("No se Pudo Conectar a Base de Dato de Casas")
            Return
        End If
        Try
            While DatosLoraWan.Leer() 'Lee una fila de datos desde la base de datos Lorawan y la almacena en datoRecibido
                If DatosCondominio.Escribir(DatosLoraWan.datoRecibido) Then 'Escribe el dato en la tabla detalle consumo casas
                    If DatosLoraWan.Leido() Then 'Marca como leido el datoRecibido en la base de datos Lorawan
                        Desplegar_Estado("Marcado como Leido")
                    End If
                Else
                    If DatosLoraWan.Leido() Then
                        Desplegar_Estado("Marcado como Leido")
                    End If
                End If
            End While
        Catch ex As Exception

        End Try
        DatosCondominio.CerrarConexion()
        bOcupado = False
    End Sub
End Module
