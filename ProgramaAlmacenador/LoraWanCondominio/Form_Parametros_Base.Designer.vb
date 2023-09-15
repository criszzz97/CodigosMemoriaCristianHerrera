<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class Form_Parametros_Base
    Inherits System.Windows.Forms.Form

    'Form reemplaza a Dispose para limpiar la lista de componentes.
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Requerido por el Diseñador de Windows Forms
    Private components As System.ComponentModel.IContainer

    'NOTA: el Diseñador de Windows Forms necesita el siguiente procedimiento
    'Se puede modificar usando el Diseñador de Windows Forms.  
    'No lo modifique con el editor de código.
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(Form_Parametros_Base))
        Me.Label_Servidor = New System.Windows.Forms.Label()
        Me.Text_Servidor = New System.Windows.Forms.TextBox()
        Me.Check_Seguridad_Windows = New System.Windows.Forms.CheckBox()
        Me.Label_Usuario = New System.Windows.Forms.Label()
        Me.Text_Usuario = New System.Windows.Forms.TextBox()
        Me.Text_Clave = New System.Windows.Forms.TextBox()
        Me.Label_Clave = New System.Windows.Forms.Label()
        Me.Button_Aceptar = New System.Windows.Forms.Button()
        Me.Button_Cancelar = New System.Windows.Forms.Button()
        Me.Label_EsperaConexion = New System.Windows.Forms.Label()
        Me.Text_EsperaConexion = New System.Windows.Forms.TextBox()
        Me.Text_EsperaComando = New System.Windows.Forms.TextBox()
        Me.Label_EperaComando = New System.Windows.Forms.Label()
        Me.Text_Base = New System.Windows.Forms.TextBox()
        Me.Label_Base = New System.Windows.Forms.Label()
        Me.SuspendLayout()
        '
        'Label_Servidor
        '
        Me.Label_Servidor.AutoSize = True
        Me.Label_Servidor.Location = New System.Drawing.Point(12, 13)
        Me.Label_Servidor.Margin = New System.Windows.Forms.Padding(1, 0, 1, 0)
        Me.Label_Servidor.Name = "Label_Servidor"
        Me.Label_Servidor.Size = New System.Drawing.Size(64, 20)
        Me.Label_Servidor.TabIndex = 0
        Me.Label_Servidor.Text = "Servidor"
        '
        'Text_Servidor
        '
        Me.Text_Servidor.Location = New System.Drawing.Point(87, 12)
        Me.Text_Servidor.Margin = New System.Windows.Forms.Padding(1, 1, 1, 1)
        Me.Text_Servidor.Name = "Text_Servidor"
        Me.Text_Servidor.Size = New System.Drawing.Size(353, 27)
        Me.Text_Servidor.TabIndex = 1
        '
        'Check_Seguridad_Windows
        '
        Me.Check_Seguridad_Windows.AutoSize = True
        Me.Check_Seguridad_Windows.Location = New System.Drawing.Point(12, 49)
        Me.Check_Seguridad_Windows.Margin = New System.Windows.Forms.Padding(1, 1, 1, 1)
        Me.Check_Seguridad_Windows.Name = "Check_Seguridad_Windows"
        Me.Check_Seguridad_Windows.Size = New System.Drawing.Size(286, 24)
        Me.Check_Seguridad_Windows.TabIndex = 2
        Me.Check_Seguridad_Windows.Text = "Usar Seguridad Integrada de Windows"
        Me.Check_Seguridad_Windows.UseVisualStyleBackColor = True
        '
        'Label_Usuario
        '
        Me.Label_Usuario.AutoSize = True
        Me.Label_Usuario.Location = New System.Drawing.Point(12, 85)
        Me.Label_Usuario.Margin = New System.Windows.Forms.Padding(1, 0, 1, 0)
        Me.Label_Usuario.Name = "Label_Usuario"
        Me.Label_Usuario.Size = New System.Drawing.Size(59, 20)
        Me.Label_Usuario.TabIndex = 3
        Me.Label_Usuario.Text = "Usuario"
        '
        'Text_Usuario
        '
        Me.Text_Usuario.Location = New System.Drawing.Point(87, 82)
        Me.Text_Usuario.Margin = New System.Windows.Forms.Padding(1, 1, 1, 1)
        Me.Text_Usuario.Name = "Text_Usuario"
        Me.Text_Usuario.Size = New System.Drawing.Size(194, 27)
        Me.Text_Usuario.TabIndex = 4
        '
        'Text_Clave
        '
        Me.Text_Clave.Location = New System.Drawing.Point(87, 114)
        Me.Text_Clave.Margin = New System.Windows.Forms.Padding(1, 1, 1, 1)
        Me.Text_Clave.Name = "Text_Clave"
        Me.Text_Clave.Size = New System.Drawing.Size(194, 27)
        Me.Text_Clave.TabIndex = 6
        '
        'Label_Clave
        '
        Me.Label_Clave.AutoSize = True
        Me.Label_Clave.Location = New System.Drawing.Point(12, 117)
        Me.Label_Clave.Margin = New System.Windows.Forms.Padding(1, 0, 1, 0)
        Me.Label_Clave.Name = "Label_Clave"
        Me.Label_Clave.Size = New System.Drawing.Size(45, 20)
        Me.Label_Clave.TabIndex = 5
        Me.Label_Clave.Text = "Clave"
        '
        'Button_Aceptar
        '
        Me.Button_Aceptar.Location = New System.Drawing.Point(304, 49)
        Me.Button_Aceptar.Margin = New System.Windows.Forms.Padding(1, 1, 1, 1)
        Me.Button_Aceptar.Name = "Button_Aceptar"
        Me.Button_Aceptar.Size = New System.Drawing.Size(134, 120)
        Me.Button_Aceptar.TabIndex = 7
        Me.Button_Aceptar.Text = "Aceptar"
        Me.Button_Aceptar.UseVisualStyleBackColor = True
        '
        'Button_Cancelar
        '
        Me.Button_Cancelar.Location = New System.Drawing.Point(304, 181)
        Me.Button_Cancelar.Margin = New System.Windows.Forms.Padding(1, 1, 1, 1)
        Me.Button_Cancelar.Name = "Button_Cancelar"
        Me.Button_Cancelar.Size = New System.Drawing.Size(134, 55)
        Me.Button_Cancelar.TabIndex = 8
        Me.Button_Cancelar.Text = "Cancelar"
        Me.Button_Cancelar.UseVisualStyleBackColor = True
        '
        'Label_EsperaConexion
        '
        Me.Label_EsperaConexion.AutoSize = True
        Me.Label_EsperaConexion.Location = New System.Drawing.Point(12, 181)
        Me.Label_EsperaConexion.Margin = New System.Windows.Forms.Padding(1, 0, 1, 0)
        Me.Label_EsperaConexion.Name = "Label_EsperaConexion"
        Me.Label_EsperaConexion.Size = New System.Drawing.Size(194, 20)
        Me.Label_EsperaConexion.TabIndex = 9
        Me.Label_EsperaConexion.Text = "Tiempo Espera Conexión [s]"
        '
        'Text_EsperaConexion
        '
        Me.Text_EsperaConexion.Location = New System.Drawing.Point(213, 181)
        Me.Text_EsperaConexion.Margin = New System.Windows.Forms.Padding(1, 1, 1, 1)
        Me.Text_EsperaConexion.Name = "Text_EsperaConexion"
        Me.Text_EsperaConexion.Size = New System.Drawing.Size(69, 27)
        Me.Text_EsperaConexion.TabIndex = 10
        '
        'Text_EsperaComando
        '
        Me.Text_EsperaComando.Location = New System.Drawing.Point(213, 213)
        Me.Text_EsperaComando.Margin = New System.Windows.Forms.Padding(1, 1, 1, 1)
        Me.Text_EsperaComando.Name = "Text_EsperaComando"
        Me.Text_EsperaComando.Size = New System.Drawing.Size(69, 27)
        Me.Text_EsperaComando.TabIndex = 12
        '
        'Label_EperaComando
        '
        Me.Label_EperaComando.AutoSize = True
        Me.Label_EperaComando.Location = New System.Drawing.Point(12, 213)
        Me.Label_EperaComando.Margin = New System.Windows.Forms.Padding(1, 0, 1, 0)
        Me.Label_EperaComando.Name = "Label_EperaComando"
        Me.Label_EperaComando.Size = New System.Drawing.Size(195, 20)
        Me.Label_EperaComando.TabIndex = 11
        Me.Label_EperaComando.Text = "Tiempo Espera Ejecución [s]"
        '
        'Text_Base
        '
        Me.Text_Base.Location = New System.Drawing.Point(87, 146)
        Me.Text_Base.Margin = New System.Windows.Forms.Padding(1, 1, 1, 1)
        Me.Text_Base.Name = "Text_Base"
        Me.Text_Base.Size = New System.Drawing.Size(194, 27)
        Me.Text_Base.TabIndex = 14
        '
        'Label_Base
        '
        Me.Label_Base.AutoSize = True
        Me.Label_Base.Location = New System.Drawing.Point(12, 149)
        Me.Label_Base.Margin = New System.Windows.Forms.Padding(1, 0, 1, 0)
        Me.Label_Base.Name = "Label_Base"
        Me.Label_Base.Size = New System.Drawing.Size(40, 20)
        Me.Label_Base.TabIndex = 13
        Me.Label_Base.Text = "Base"
        '
        'Form_Parametros_Base
        '
        Me.AcceptButton = Me.Button_Aceptar
        Me.AutoScaleDimensions = New System.Drawing.SizeF(8.0!, 20.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.CancelButton = Me.Button_Cancelar
        Me.ClientSize = New System.Drawing.Size(448, 247)
        Me.Controls.Add(Me.Text_Base)
        Me.Controls.Add(Me.Label_Base)
        Me.Controls.Add(Me.Text_EsperaComando)
        Me.Controls.Add(Me.Label_EperaComando)
        Me.Controls.Add(Me.Text_EsperaConexion)
        Me.Controls.Add(Me.Label_EsperaConexion)
        Me.Controls.Add(Me.Button_Cancelar)
        Me.Controls.Add(Me.Button_Aceptar)
        Me.Controls.Add(Me.Text_Clave)
        Me.Controls.Add(Me.Label_Clave)
        Me.Controls.Add(Me.Text_Usuario)
        Me.Controls.Add(Me.Label_Usuario)
        Me.Controls.Add(Me.Check_Seguridad_Windows)
        Me.Controls.Add(Me.Text_Servidor)
        Me.Controls.Add(Me.Label_Servidor)
        Me.Icon = CType(resources.GetObject("$this.Icon"), System.Drawing.Icon)
        Me.Margin = New System.Windows.Forms.Padding(1, 1, 1, 1)
        Me.Name = "Form_Parametros_Base"
        Me.Text = "Parámetros Base de Dato"
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub

    Friend WithEvents Label_Servidor As Label
    Friend WithEvents Text_Servidor As TextBox
    Friend WithEvents Check_Seguridad_Windows As CheckBox
    Friend WithEvents Label_Usuario As Label
    Friend WithEvents Text_Usuario As TextBox
    Friend WithEvents Text_Clave As TextBox
    Friend WithEvents Label_Clave As Label
    Friend WithEvents Button_Aceptar As Button
    Friend WithEvents Button_Cancelar As Button
    Friend WithEvents Label_EsperaConexion As Label
    Friend WithEvents Text_EsperaConexion As TextBox
    Friend WithEvents Text_EsperaComando As TextBox
    Friend WithEvents Label_EperaComando As Label
    Friend WithEvents Text_Base As TextBox
    Friend WithEvents Label_Base As Label
End Class
