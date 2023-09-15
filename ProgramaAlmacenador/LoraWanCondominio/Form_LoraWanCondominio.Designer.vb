<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()>
Partial Class Form_LoraWanCondominio
    Inherits System.Windows.Forms.Form

    'Form overrides dispose to clean up the component list.
    <System.Diagnostics.DebuggerNonUserCode()>
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()>
    Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container()
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(Form_LoraWanCondominio))
        Me.List_Estado = New System.Windows.Forms.ListBox()
        Me.Timer_Procesamiento = New System.Windows.Forms.Timer(Me.components)
        Me.Button_Base_LoraWan = New System.Windows.Forms.Button()
        Me.Button_Base_Casas = New System.Windows.Forms.Button()
        Me.Button_Leer = New System.Windows.Forms.Button()
        Me.SuspendLayout()
        '
        'List_Estado
        '
        Me.List_Estado.FormattingEnabled = True
        Me.List_Estado.ItemHeight = 20
        Me.List_Estado.Location = New System.Drawing.Point(10, 12)
        Me.List_Estado.Margin = New System.Windows.Forms.Padding(1)
        Me.List_Estado.Name = "List_Estado"
        Me.List_Estado.Size = New System.Drawing.Size(701, 344)
        Me.List_Estado.TabIndex = 0
        '
        'Timer_Procesamiento
        '
        Me.Timer_Procesamiento.Enabled = True
        Me.Timer_Procesamiento.Interval = 10000
        '
        'Button_Base_LoraWan
        '
        Me.Button_Base_LoraWan.Image = Global.LoraWanCondominio.My.Resources.Resources.Config_Base50
        Me.Button_Base_LoraWan.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft
        Me.Button_Base_LoraWan.Location = New System.Drawing.Point(294, 363)
        Me.Button_Base_LoraWan.Margin = New System.Windows.Forms.Padding(1)
        Me.Button_Base_LoraWan.Name = "Button_Base_LoraWan"
        Me.Button_Base_LoraWan.Size = New System.Drawing.Size(195, 60)
        Me.Button_Base_LoraWan.TabIndex = 1
        Me.Button_Base_LoraWan.Text = "Parámetros Base de Dato LoraWan"
        Me.Button_Base_LoraWan.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText
        Me.Button_Base_LoraWan.UseVisualStyleBackColor = True
        '
        'Button_Base_Casas
        '
        Me.Button_Base_Casas.Image = Global.LoraWanCondominio.My.Resources.Resources.Config_Base50
        Me.Button_Base_Casas.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft
        Me.Button_Base_Casas.Location = New System.Drawing.Point(514, 363)
        Me.Button_Base_Casas.Margin = New System.Windows.Forms.Padding(1)
        Me.Button_Base_Casas.Name = "Button_Base_Casas"
        Me.Button_Base_Casas.Size = New System.Drawing.Size(195, 60)
        Me.Button_Base_Casas.TabIndex = 2
        Me.Button_Base_Casas.Text = "Párametros Base de Dato de Casas"
        Me.Button_Base_Casas.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText
        Me.Button_Base_Casas.UseVisualStyleBackColor = True
        '
        'Button_Leer
        '
        Me.Button_Leer.Location = New System.Drawing.Point(10, 366)
        Me.Button_Leer.Name = "Button_Leer"
        Me.Button_Leer.Size = New System.Drawing.Size(123, 57)
        Me.Button_Leer.TabIndex = 3
        Me.Button_Leer.Text = "Leer"
        Me.Button_Leer.UseVisualStyleBackColor = True
        '
        'Form_LoraWanCondominio
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(8.0!, 20.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(720, 435)
        Me.Controls.Add(Me.Button_Leer)
        Me.Controls.Add(Me.Button_Base_Casas)
        Me.Controls.Add(Me.Button_Base_LoraWan)
        Me.Controls.Add(Me.List_Estado)
        Me.Icon = CType(resources.GetObject("$this.Icon"), System.Drawing.Icon)
        Me.Margin = New System.Windows.Forms.Padding(1)
        Me.Name = "Form_LoraWanCondominio"
        Me.Text = "Traspaso Datos LoraWan a Casas"
        Me.ResumeLayout(False)

    End Sub

    Private Sub Form_LoraWanCondominio_Load(sender As Object, e As EventArgs) Handles Me.Load
        Mod_LoraWanCondominio.Iniciar()
    End Sub

    Friend WithEvents List_Estado As ListBox
    Friend WithEvents Timer_Procesamiento As Timer
    Friend WithEvents Button_Base_LoraWan As Button
    Friend WithEvents Button_Base_Casas As Button
    Friend WithEvents Button_Leer As Button
End Class
