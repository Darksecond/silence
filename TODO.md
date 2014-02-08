TODO
====

* System
** init() -> opens window, start opengl, setRoot
** kill/deinit() -> closes window, stop opengl, release assets
** update() -> updates Timer, Song, SyncManager
** Timer
** Song
** GLWindow

* Mesh
** Wireframe mode
** Point cloud mode
** OBJ loader

* TextureManager
** Texture parameters (changeable per texture) -> TextureParameters class/struct, pass into Texture when creating, or update Texture if it already exists. Should cover it.
   Texture parameters like, wrap, filtering, mipmap on/off, etc
** Empty texture, for FBO usage.

* MeshManager
** Singleton
** load(name)
** unload(name)
** get(name) : Mesh&
** Primitive(s)
*** Generate (simple) meshes on the fly -> Cube, Sphere, Quad (fullscreen)
** OBJ loader

* SyncManager -> Uses Timer
** Event
** TriggerSystem
*** Trigger
** BPM

* Parameters -> In Virta this is a singleton, with namespaces.
** namespaces

* Parser
** namespace (-> parameters)
** config
** texture (parameters)
** mesh (parameters)
** material
** trigger
** bpm
** event
** render target (renderbuffer)
** fbo

* Timer
** Seems to be just a timer, no delta calculations.
   This also means it runs in (milli/micro)seconds.
   Although it does have a sync with the music. -> Can sync make Timer go backwards in time? or just not forwards any?
** update()
** getTime()
** setPaused(paused : bool)
* Frametimer
** This is the actual frame timer, or 'main loop'
   Every scene has it's own frame timer
   (i'm guessing so different scenes can have different update rates)
   This *does* provide a delta() method.
   It also provides stepsLeft, endStep and other method to control the steps.
** At least, this is how Virta does it. I might do it differently.

* Demo
** This has a timeline of all scenes
   Every timeline entry has a start and stop time attached.
** Scene
*** init()
*** deinit()
*** update(delta) -> delta might not even be needed, since update steps *should* always be the same size.
*** draw(alpha) -> alpha is optional
*** setPosition(pos) -> Position is a float between 0.0 and 1.0.
*** Scenes have no knowledge about what their absolute start and end times are.
    They run from 0.0 to 1.0 position.

* Postprocess
* Framebuffer Object
** Render target (renderbuffer)
** Render to texture
* Material

* Music
** OpenAL/Fmod/...
** Syncronisation with Timer
