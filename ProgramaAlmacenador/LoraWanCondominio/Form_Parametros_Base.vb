Public Class Form_Parametros_Base
    Public bSalir As Boolean = False
    Public bGuardar As Boolean = False
    Private Sub Button_Aceptar_Click(sender As Object, e As EventArgs) Handles Button_Aceptar.Click
        bGuardar = True
        bSalir = True
        Close()
    End Sub

    Private Sub Button_Cancelar_Click(sender As Object, e As EventArgs) Handles Button_Cancelar.Click
        bSalir = True
        Close()
    End Sub

    Private Sub Form_Parametros_Base_Closed(sender As Object, e As EventArgs) Handles Me.Closed
        bSalir = True
    End Sub
End Class