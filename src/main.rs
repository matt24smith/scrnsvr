use std::ffi::{c_int, CString};
use std::thread::sleep;
use std::time::Duration;

/* these structs imported from C libX11 */
/* https://www.x.org/releases/X11R7.6/doc/libX11/specs/libX11/libX11.html */

#[repr(C)]
struct Display;

#[repr(C)]
struct XScreenSaverInfo;

#[link(name = "X11")]
extern "C" {
    fn XOpenDisplay(dpy: CString) -> *mut Display;
    fn XCloseDisplay(dpy: *mut Display);
    fn XScreenSaverAllocInfo() -> *mut XScreenSaverInfo;
    fn XFree(info: *mut XScreenSaverInfo);
}

extern "C" {
    fn check_timer(dpy: *mut Display, info: *mut XScreenSaverInfo) -> c_int;
}

fn main() {
    unsafe {
        let mut dpy_id = std::env::var("DISPLAY").unwrap_or(":0.0".to_string());
        dpy_id.push('\0');
        let dpy = XOpenDisplay(
            CString::from_vec_with_nul(dpy_id.as_bytes().to_vec())
                .expect(&format!("Opening display {}", &dpy_id)),
        );
        let info = XScreenSaverAllocInfo();

        loop {
            if check_timer(dpy, info) != 0 {
                XFree(info);
                XCloseDisplay(dpy);
                std::process::exit(1);
            } else {
                sleep(Duration::from_secs(5));
            }
        }
    }
}
