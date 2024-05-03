fn main() {
    println!("cargo:rustc-link-arg=/usr/lib/libXss.so");
    println!("cargo:rustc-link-arg=/usr/lib/libX11.so");
    println!("cargo:rerun-if-changed=src/getIdleTime.c");
    cc::Build::new()
        .file("src/lib.c")
        .flag("-Werror")
        .flag("-std=c17")
        .flag("-nostartfiles")
        .compile("saver.a");
}
