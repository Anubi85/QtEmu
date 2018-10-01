INCLUDEPATH += \
    ../Includes

CONFIG(debug, debug|release): {
    DESTDIR = $${PWD}/Bin/$${TARGET}/Debug
    OBJECTS_DIR = $${PWD}/$${TARGET}/Obj/Debug
}
CONFIG(release, debug|release): {
    DESTDIR = $${PWD}/Bin/$${TARGET}/Release
    OBJECTS_DIR = $${PWD}/$${TARGET}/Obj/Release
}

defineReplace(AddLibraryReference) {
    libraryPath = $$1
    libraryName = $$2
    #get current extension for library and copy command
    win32: {
        FILE_EXT = *.dll
        COPY_CMD = copy
    }
    unix: !macx {
        FILE_EXT = *.so
        COPY_CMD = cp
    }
    macx {
        FILE_EXT = *.dylib
        COPY_CMD = cp
    }
    #add library to linker and copy the library files to output directory
    CONFIG(debug, debug|release): {
        LIBS += -L$${libraryPath}/$${libraryName}/debug/ -l$${libraryName}
        QMAKE_POST_LINK += $$quote($${COPY_CMD} $$shell_quote($$shell_path($${libraryPath}/$${libraryName}/debug/))$${FILE_EXT} $$shell_quote($${DESTDIR}))
    }
    CONFIG(release, debug|release): {
        LIBS += -L$${libraryPath}/$${libraryName}/release/ -l$${libraryName}
        QMAKE_POST_LINK += $$quote($${COPY_CMD} $$shell_quote($$shell_path($${libraryPath}/$${libraryName}/release/))$${FILE_EXT} $$shell_quote($${DESTDIR}))
    }
    equals(3, "") {
        QMAKE_POST_LINK += $$quote( && )
    }
    export(LIBS)
    export(QMAKE_POST_LINK)
    return(done)
}
