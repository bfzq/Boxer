/* 
 Boxer is copyright 2009 Alun Bestor and contributors.
 Boxer is released under the GNU General Public License 2.0. A full copy of this license can be
 found in this XCode project at Resources/English.lproj/GNU General Public License.txt, or read
 online at [http://www.gnu.org/licenses/gpl-2.0.txt].
 */


//This header defines C++-facing hooks which Boxer has injected into DOSBox functions, to wrest
//control from them at opportune moments. The functions herein are defined in various BXEmulator
//source files.

#ifndef BOXER
#define BOXER

#if __cplusplus
extern "C" {
#endif

#import <SDL/SDL.h>
#import "config.h"

#define BOXER_EXPORT __attribute__((visibility("default")))

//Called from sdlmain.cpp: perform various notifications and overrides.
BOXER_EXPORT bool boxer_handleEventLoop();
BOXER_EXPORT bool boxer_handleSDLEvent(SDL_Event *event);
BOXER_EXPORT bool boxer_handleDOSBoxTitleChange(int cycles, int frameskip, bool paused);
BOXER_EXPORT void boxer_applyConfigFiles();
BOXER_EXPORT void boxer_setupSurfaceScaled(Bit32u sdl_flags, Bit32u bpp);
BOXER_EXPORT void boxer_copySurfaceSize(unsigned int * surfaceWidth, unsigned int * surfaceHeight);
BOXER_EXPORT Bit8u boxer_screenColorDepth();

//Called from render.cpp: configures the DOSBox render state.
BOXER_EXPORT void boxer_applyRenderingStrategy();

//Called from messages.cpp: overrides DOSBox's translation system.
BOXER_EXPORT const char * boxer_localizedStringForKey(char const * key);

//Called from dos_keyboard_layout.cpp: provides the current OS X keyboard layout as a DOSBox layout code.
BOXER_EXPORT const char * boxer_currentDOSKeyboardLayout();

//Called from dos_programs.cpp: verifies that DOSBox is allowed to mount the specified folder.
BOXER_EXPORT bool boxer_willMountPath(const char *pathStr);

//Called from hardware.cpp: overrides DOSBox's image capture paths.
BOXER_EXPORT const char * boxer_pathForNewRecording(const char * extension);

//Called from shell.cpp: notifies Boxer when autoexec.bat is run.
BOXER_EXPORT void boxer_handleAutoexecStart();
BOXER_EXPORT void boxer_handleAutoexecEnd();

//Called from shell.cpp: notifies Boxer when control returns to the DOS prompt.
BOXER_EXPORT void boxer_handleReturnToShell();

//Called from shell_cmds.cpp: hooks into shell command processing.
BOXER_EXPORT bool boxer_handleShellCommand(char* cmd, char* args);
	
//Called from drive_cache.cpp: allows Boxer to hide OS X files that DOSBox shouldn't touch.
BOXER_EXPORT bool boxer_allowFileWithName(const char *name);

//Called from drive_local.cpp: allows Boxer to restrict access to files that DOS programs shouldn't write to.
class DOS_Drive;
BOXER_EXPORT bool boxer_allowWriteAccessToPathOnDrive(const char *filename, DOS_Drive *drive);
	
//Called from dos_programs.cpp et al: informs Boxer of drive mount/unmount events
BOXER_EXPORT void boxer_syncDriveCache();

//Called from dosbox.cpp to short-circuit the emulation loop
BOXER_EXPORT bool boxer_isPaused();
BOXER_EXPORT bool boxer_isCancelled();
	
#if __cplusplus
} //Extern C
#endif

#endif