//CodigosTTN
-Estos códigos corren en la aplicación web Things Network y son usados tanto para codificar mensajes (downlinks) provenientes de la aplicación y
transformarlos en bytes entendibles por el dispositivo como para decodificar bytes recibidos desde el dispositivo final (uplinks) y tranformarlos
en un valor legible por la aplicación.

//Programa Principal
-Este programa contiene los códigos escenciales para crear una interfaz gráfica capaz de monitorear el estado
de los sensores de flujo de agua, aplicar reglas de consumo y manipular las válvulas directamente.

-Este proyecto posee los siguientes archivos:

└───ProgramaPrincipal
        actuador.cpp
        actuador.h
        casa.cpp
        casa.h
        casaboton.cpp
        casaboton.h
        casainiciovsta.cpp
        casainiciovsta.h
        casainiciovsta.ui
        casaview.cpp
        casaview.h
        condominio.cpp
        condominio.h
        condominioview.cpp
        condominioview.h
        configuracioncasas.cpp
        configuracioncasas.h
        configuracioncasas.ui
        configuracionescondominio.cpp
        configuracionescondominio.h
        configuracionescondominioview.cpp
        configuracionescondominioview.h
        configuracionescondominioview.ui
        datosconsumo.cpp
        datosconsumo.h
        detallescondominios.cpp
        detallescondominios.h
        detallescondominios.ui
        FechaAustralianaAChilena.h
        grafico.cpp
        grafico.h
        main.cpp
        nodo.cpp
        nodo.h
        ProyectoELO308.pro
        ProyectoELO308.pro.user
        proyectomemoria.cpp
        proyectomemoria.h
        proyectomemoria.ui
        sensor.cpp
        sensor.h
        sensorflujo.cpp
        sensorflujo.h
        timerreglas.cpp
        timerreglas.h
        valvula.cpp
        valvula.h


-Para ejecutar este programao, en primer lugar se deben descargar todos los archivos relacionados al proyecto en una carpeta especifica,
posteriormente se debe abrir la aplicacion de QT ProyectoELO308 (se debe tener instalado el framework QT previamente) y dentro 
de la aplicación selecciona debug para correr el programa.

//Programa Almacenador
-Este proyecto contiene los códigos escenciales para crear un programa capaz de pasar los datos desde una base de datos crudos (captura) 
a una de procesamiento, donde se provee una interfaz gráfica con la cual se puede realizar esto.

-Este proyecto posee los siguientes archivos:

├───ProgramaAlmacenador
│   │   LoraWanCondominio.sln
│   │
│   ├───Imagenes
│   │       Config_Base30.png
│   │       Config_Base50.png
│   │
│   └───LoraWanCondominio
│       │   ApplicationEvents.vb
│       │   Cls_DatosCondominio.vb
│       │   Cls_DatosLoraWan.vb
│       │   Cls_ParametrosConexionBaseDato.vb
│       │   Form_LoraWanCondominio.Designer.vb
│       │   Form_LoraWanCondominio.resx
│       │   Form_LoraWanCondominio.vb
│       │   Form_Parametros_Base.Designer.vb
│       │   Form_Parametros_Base.resx
│       │   Form_Parametros_Base.vb
│       │   LoraWanCondominio.vbproj
│       │   LoraWanCondominio.vbproj.user
│       │   Mod_Logs.vb
│       │   Mod_LoraWanCondominio.vb
│       │   Mod_Modificacion_BaseDato.vb
│       │
│       ├───bin
│       │   └───Debug
│       │       └───net6.0-windows
│       │           └───ref
│       ├───My Project
│       │       Application.Designer.vb
│       │       Application.myapp
│       │       Resources.Designer.vb
│       │       Resources.resx
│       │
│       └───obj
│           │   LoraWanCondominio.vbproj.nuget.dgspec.json
│           │   LoraWanCondominio.vbproj.nuget.g.props
│           │   LoraWanCondominio.vbproj.nuget.g.targets
│           │   project.assets.json
│           │   project.nuget.cache
│           │
│           └───Debug
│               └───net6.0-windows
│                   │   .NETCoreApp,Version=v6.0.AssemblyAttributes.vb
│                   │   LoraWanCondominio.AssemblyInfo.vb
│                   │   LoraWanCondominio.AssemblyInfoInputs.cache
│                   │   LoraWanCondominio.assets.cache
│                   │   LoraWanCondominio.GeneratedMSBuildEditorConfig.editorconfig
│                   │   LoraWanCondominio.vbproj.AssemblyReference.cache


-Para ejecutar este programa, en primer lugar se deben descargar todos los archivos relacionados al proyecto en una carpeta especifica,
posteriormente se debe abrir esta carpeta en un proyecto de visual studio (se debe tener instalado visual studio 2022 previamente) y 
dentro del software, el proyecto LoraWanCondominio.sln se debe compilar y posteriormente ejecutar.
 
//Programa Captura
Este proyecto contiene los códigos escenciales para levantar un servidor capaz de recibir webhooks provenientes de la pagina The Things Network y 
almacenar la información en la base de datos de Captura.

-Este proyecto posee los siguientes archivos:


├───ProgramaCaptura
│   │   appsettings.Development.json
│   │   CapturaLora.csproj
│   │   CapturaLora.csproj.user
│   │   Program.cs
│   │   Startup.cs
│   │
│   ├───.config
│   │       dotnet-tools.json
│   │
│   ├───Controllers
│   │       UpLinksController.cs
│   │
│   ├───Data
│   │       CapturaLoraContext.cs
│   │
│   ├───Models
│   │       UpLink.cs
│   │
│   └───Properties
│       │   launchSettings.json
│       │   serviceDependencies.json
│       │   serviceDependencies.local.json
│       │   serviceDependencies.local.json.user
│       │
│       └───PublishProfiles
│               FolderProfile.pubxml
│               FolderProfile.pubxml.user
│

-Para ejecutar este programa, en primer lugar se deben descargar todos los archivos relacionados al proyecto en una carpeta especifica,
posteriormente se debe abrir esta carpeta en un proyecto de visual studio (se debe tener instalado visual studio 2022 previamente) y 
dentro del software, el proyecto este se debe compilar y posteriormente ejecutar LoraWanCondominio.vbproj.


