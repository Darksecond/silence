TODO
====

* TextureManager
** Texture parameters (changeable per texture)

* MeshManager
** Singleton
** load(name)
** unload(name)
** get(name) : Mesh&
** Primitive(s)
*** Generate (simple) meshes on the fly
** Obj loader

* SyncManager
** Event
** TriggerSystem
*** Trigger
** BPM

* Parameters
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
** render target

* Timer
** Seems to be just a timer, no delta calculations.
   This also means it runs in (milli/micro)seconds.
   Although it does have a sync with the music. -> Can sync put make Timer go backwards in time? or just not forwards any?
** update()
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
* FrameBufferObject
* Render target (FBO)
* Material

* Music
** OpenAL/Fmod/...
** Syncronisation with Timer
