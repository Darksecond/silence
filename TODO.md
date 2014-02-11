TODO
====

* Scene
** Scene should not load resources, only 'get' them.

* TextureManager & ProgramManager
** Optimize loading something twice

* Loading screen

* Mesh
** Wireframe mode
** Point cloud mode
** OBJ loader

* TextureManager
** Texture parameters (changeable per texture) -> TextureParameters class/struct, pass into Texture when creating, or update Texture if it already exists. Should cover it.
   Texture parameters like, wrap, filtering, mipmap on/off, etc
** Specify texture parameters on 'load'.
** Empty texture, for FBO usage.

* MeshManager
** Singleton
** load(name)
** unload(name)
** get(name) : Mesh&
** Primitive(s)
*** Generate (simple) meshes on the fly -> Cube, Sphere, Quad (fullscreen)
** OBJ loader

* SyncManager
** update -> called from System
** BPM

* Parameters -> In Virta this is a singleton, with namespaces.
** namespaces

* Parser
** Make parser load textures, meshes and programs
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

* Postprocess
* Framebuffer Object
** Render target (renderbuffer)
** Render to texture
* Material

* Music
** OpenAL/Fmod/...
** Syncronisation with Timer
