Imports System.Threading

Public Class Form_LoraWanCondominio
    Private bOcupado As Boolean = False

    'Esta funcion maneja el evento de un tick de timer la cual llama a TimerProcesamiento() lo
    'cual implica que se guarden datos, siempre y cuando no se este ocupado configurando las conexiones de bases de datos.
    Private Sub Timer_Procesamiento_Tick(sender As Object, e As EventArgs) Handles Timer_Procesamiento.Tick
        If Not bOcupado Then
            Mod_LoraWanCondominio.TimerProcesamiento()
        End If
    End Sub

    'Esta funcion maneja un evento que al recibir un click en el boton grafico de Base_LoraWan abre un nuevo dialog
    'en donde se configura la conexión a la base de datos de Lorawan.
    Private Sub Button_Base_LoraWan_Click(sender As Object, e As EventArgs) Handles Button_Base_LoraWan.Click
        bOcupado = True
        Button_Base_LoraWan.Enabled = False
        Dim FormBase As Form_Parametros_Base = New Form_Parametros_Base()
        'Inicializa valores por defecto
        FormBase.Text_Servidor.Text = PaBaseLoraWan.sServidor
        FormBase.Check_Seguridad_Windows.Checked = PaBaseLoraWan.bSeguridadWindows
        FormBase.Text_Usuario.Text = PaBaseLoraWan.sUsuario
        FormBase.Text_Clave.Text = PaBaseLoraWan.sClave
        FormBase.Text_Base.Text = PaBaseLoraWan.sBase
        FormBase.Text_EsperaConexion.Text = PaBaseLoraWan.EsperaConexion.ToString()
        FormBase.Text_EsperaComando.Text = PaBaseLoraWan.EsperaComando.ToString()
        FormBase.ShowDialog()
        If FormBase.bGuardar Then
            'Inicializa y configura nuevos valores
            PaBaseLoraWan.sServidor = FormBase.Text_Servidor.Text.Trim()
            PaBaseLoraWan.bSeguridadWindows = FormBase.Check_Seguridad_Windows.Checked
            PaBaseLoraWan.sUsuario = FormBase.Text_Usuario.Text.Trim()
            PaBaseLoraWan.sClave = FormBase.Text_Clave.Text.Trim()
            PaBaseLoraWan.sBase = FormBase.Text_Base.Text.Trim()
            Try
                PaBaseLoraWan.EsperaConexion = Integer.Parse(FormBase.Text_EsperaConexion.Text)
            Catch ex As Exception
                Desplegar_Estado(ex.Message)
            End Try
            Try
                PaBaseLoraWan.EsperaComando = Integer.Parse(FormBase.Text_EsperaComando.Text)
            Catch ex As Exception
                Desplegar_Estado(ex.Message)
            End Try
            PaBaseLoraWan.ArmarConexion() 'En base a los datos asignados en los distintos atributos de PaBaseLoraWan, arma la conexion
            EscribirParametrosBaseLoraWan() 'Llama a una funcion en el modulo Mod_LoraWanCondominio la cual escribe a su vez los datos de configuracion de la base de datos en una carpeta especifica de Lorawan
        End If
        Button_Base_LoraWan.Enabled = True
        bOcupado = False
    End Sub

    'Esta funcion maneja un evento que al recibir un click en el boton grafico de Base_Casas abre un nuevo dialog
    'en donde se configura la conexión a la base de datos de las casas.
    Private Sub Button_Base_Casas_Click(sender As Object, e As EventArgs) Handles Button_Base_Casas.Click
        bOcupado = True
        Button_Base_Casas.Enabled = False
        Dim FormBase As Form_Parametros_Base = New Form_Parametros_Base()
        'Inicializa valores por defecto
        FormBase.Text_Servidor.Text = PaBaseCasas.sServidor
        FormBase.Check_Seguridad_Windows.Checked = PaBaseCasas.bSeguridadWindows
        FormBase.Text_Usuario.Text = PaBaseCasas.sUsuario
        FormBase.Text_Clave.Text = PaBaseCasas.sClave
        FormBase.Text_Base.Text = PaBaseCasas.sBase
        FormBase.Text_EsperaConexion.Text = PaBaseCasas.EsperaConexion.ToString()
        FormBase.Text_EsperaComando.Text = PaBaseCasas.EsperaComando.ToString()
        FormBase.ShowDialog()
        If FormBase.bGuardar Then
            'Inicializa y configura nuevos valores
            PaBaseCasas.sServidor = FormBase.Text_Servidor.Text.Trim()
            PaBaseCasas.bSeguridadWindows = FormBase.Check_Seguridad_Windows.Checked
            PaBaseCasas.sUsuario = FormBase.Text_Usuario.Text.Trim()
            PaBaseCasas.sClave = FormBase.Text_Clave.Text.Trim()
            PaBaseCasas.sBase = FormBase.Text_Base.Text.Trim()
            Try
                PaBaseCasas.EsperaConexion = Integer.Parse(FormBase.Text_EsperaConexion.Text) 'Tiempo de espera de una conexion antes de que ocurra un timeout
            Catch ex As Exception
                Desplegar_Estado(ex.Message)
            End Try
            Try
                PaBaseCasas.EsperaComando = Integer.Parse(FormBase.Text_EsperaComando.Text) 'Tiempo de espera para la transaccion de query SQL antes de que ocurra un timeout
            Catch ex As Exception
                Desplegar_Estado(ex.Message)
            End Try
            PaBaseCasas.ArmarConexion() 'En base a los datos asignados en los distintos atributos de PaBaseCasas, arma la conexion
            EscribirParametrosBaseCasas() 'Llama a una funcion en el modulo Mod_LoraWanCondominio la cual escribe a su vez los datos de configuracion de la base de datos en una carpeta especifica de casas
        End If
        Button_Base_Casas.Enabled = True
        bOcupado = False
    End Sub

    'Esta funcion maneja un evento que al recibir un click en el boton leer inicia el timer de
    'procesamiento lo cual implica que se inice la secuencia de guardado de datos inmediatamente,
    'donde las conexiones a las bases de datos deben estar previamente configuradas
    Private Sub Button_Leer_Click(sender As Object, e As EventArgs) Handles Button_Leer.Click
        TimerProcesamiento()
    End Sub
End Class
