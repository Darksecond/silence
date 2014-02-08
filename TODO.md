TODO
====

* System
** input stuff (getKeyPressed)

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
** setTime(...)
** changeTime(...)

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
