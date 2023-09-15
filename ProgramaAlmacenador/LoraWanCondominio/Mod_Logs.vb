Imports System.Globalization
Imports System.IO

Module Mod_Logs
    Public lHubo_Error As Boolean = False
    Public sMensaje_Error = ""
    Public Sub Desplegar_Estado(ByVal sEstado As String, ByVal sDesp As ListBox)
        sEstado = DateTime.Now.ToString(CultureInfo.InvariantCulture) + " - " + sEstado
        sDesp.Items.Add(sEstado)
        If sDesp.Items.Count > 400 Then
            Dim i As Integer
            For i = 0 To 100
                sDesp.Items.RemoveAt(1)
            Next
        End If
        If sDesp.Items.Count > 20 Then
            sDesp.SelectedIndex = sDesp.Items.Count - 1
        End If
        Log_Estado(sEstado)
        Application.DoEvents()
    End Sub

    Public Sub Desplegar_Estado(sEstado As String)
        Desplegar_Estado(sEstado, Form_LoraWanCondominio.List_Estado)
    End Sub

    Private Sub Log_Estado(ByVal sEstado As String)
        Dim sCarpetaLog As String = Application.CommonAppDataPath + "\Log_LoraWanCondominio"
        Dim sArchivoLog As String = "Log_" + Now().Year().ToString() + "_" + Now().Month().ToString() + "_" + Now().Day().ToString() + ".txt"
        If Not System.IO.Directory.Exists(sCarpetaLog) Then
            System.IO.Directory.CreateDirectory(sCarpetaLog)
        End If
        If Not System.IO.File.Exists(sCarpetaLog + "\" + sArchivoLog) Then
            Dim fs As FileStream = New FileStream(sCarpetaLog + "\" + sArchivoLog, FileMode.OpenOrCreate, FileAccess.ReadWrite)
            Dim s As StreamWriter = New StreamWriter(fs)
            s.Close()
            fs.Close()
        End If

        Dim fs1 As FileStream = New FileStream(sCarpetaLog + "\" + sArchivoLog, FileMode.Append, FileAccess.Write)
        Dim s1 As StreamWriter = New StreamWriter(fs1)
        s1.WriteLine(sEstado)
        s1.Close()
        fs1.Close()
        Exit Sub
    End Sub

    Public Sub Eliminar_Logs()
        Eliminar_Logs("Log_Mantenedor")
    End Sub

    Private Sub Eliminar_Logs(sCarpeta As String)
        Dim fAct As Date = Now()
        Dim iAnoAct As Integer = fAct.Year()
        Dim iMesAct As Integer = fAct.Month()
        Dim sCarpetaLog As String = Application.CommonAppDataPath + "\" + sCarpeta
        Dim iInicio As Integer = 2
        If iMesAct > 2 Then iInicio = 1
        For iDel As Integer = iInicio To 6
            Dim iAnoDel As Integer = iAnoAct - iDel
            Dim SArchivoElim As String = "Log_" + iAnoDel.ToString() + "_*.txt"
            Dim sDir As String = Dir(sCarpetaLog + "\" + SArchivoElim)
            While sDir.Length > 0
                Try
                    File.Delete(sCarpetaLog + "\" + sDir)
                Catch ex As Exception
                    Exit Sub
                End Try
                sDir = Dir(sCarpetaLog + "\" + SArchivoElim)
            End While
        Next
        If iMesAct > 2 Then
            For iMesDel As Integer = (iMesAct - 2) To 1 Step -1
                Dim SArchivoElim As String = "Log_" + iAnoAct.ToString() + "_" + iMesDel.ToString() + "_*.txt"
                Dim sDir As String = Dir(sCarpetaLog + "\" + SArchivoElim)
                While sDir.Length > 0
                    Try
                        File.Delete(sCarpetaLog + "\" + sDir)
                    Catch ex As Exception
                        Exit Sub
                    End Try
                    sDir = Dir(sCarpetaLog + "\" + SArchivoElim)
                End While
            Next
        Else
            Dim iAnoAnt As Integer = iAnoAct - 1
            For iMesDel As Integer = (iMesAct + 10) To 1 Step -1
                Dim SArchivoElim As String = "Log_" + iAnoAnt.ToString() + "_" + iMesDel.ToString() + "_*.txt"
                Dim sDir As String = Dir(sCarpetaLog + "\" + SArchivoElim)
                While sDir.Length > 0
                    Try
                        File.Delete(sCarpetaLog + "\" + sDir)
                    Catch ex As Exception
                        Exit Sub
                    End Try
                    sDir = Dir(sCarpetaLog + "\" + SArchivoElim)
                End While
            Next
        End If
    End Sub

End Module
