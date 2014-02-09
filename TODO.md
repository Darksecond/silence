TODO
====

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

* SyncManager
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

* Postprocess
* Framebuffer Object
** Render target (renderbuffer)
** Render to texture
* Material

* Music
** OpenAL/Fmod/...
** Syncronisation with Timer
