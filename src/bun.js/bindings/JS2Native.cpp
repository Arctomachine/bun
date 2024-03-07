#include "JS2Native.h"

#include <JavaScriptCore/BuiltinUtils.h>
#include <JavaScriptCore/JSFunction.h>
#include <JavaScriptCore/JSGlobalObject.h>

#include "ZigGlobalObject.h"
#include "GeneratedJS2Native.h"
#include "wtf/Assertions.h"

extern "C" JSC::EncodedJSValue ByteBlob__JSReadableStreamSource__load(JSC::JSGlobalObject* global);
extern "C" JSC::EncodedJSValue FileReader__JSReadableStreamSource__load(JSC::JSGlobalObject* global);
extern "C" JSC::EncodedJSValue ByteStream__JSReadableStreamSource__load(JSC::JSGlobalObject* global);

namespace Bun {
namespace JS2Native {

enum ReadableStreamTag : int32_t {
    Invalid = -1,

    /// ReadableStreamDefaultController or ReadableByteStreamController
    JavaScript = 0,

    /// ReadableByteStreamController
    /// but with a BlobLoader
    /// we can skip the BlobLoader and just use the underlying Blob
    Blob = 1,

    /// ReadableByteStreamController
    /// but with a FileLoader
    /// we can skip the FileLoader and just use the underlying File
    File = 2,

    /// This is a direct readable stream
    /// That means we can turn it into whatever we want
    Direct = 3,

    // This is an ambiguous stream of bytes
    Bytes = 4,
};

// This is the implementation of the generated $lazy
JSC_DEFINE_HOST_FUNCTION(jsDollarLazy, (JSC::JSGlobalObject * lexicalGlobalObject, JSC::CallFrame* callFrame))
{
    JSC::JSValue target = callFrame->uncheckedArgument(0);

#if BUN_DEBUG
    ASSERT_WITH_MESSAGE(target.isInt32(), "In call to $lazy: expected Int32, got %s", target.toWTFString(lexicalGlobalObject).utf8().data());
#endif

    int id = target.asInt32();
    if (LIKELY(id < 0)) {
        return JSValue::encode(JS2NativeGenerated::js2nativePointers[-id - 1](
            static_cast<Zig::GlobalObject*>(lexicalGlobalObject)));
    }

    switch (id) {
    case ReadableStreamTag::Blob: {
        return ByteBlob__JSReadableStreamSource__load(lexicalGlobalObject);
    }
    case ReadableStreamTag::File: {
        return FileReader__JSReadableStreamSource__load(lexicalGlobalObject);
    }
    case ReadableStreamTag::Bytes: {
        return ByteStream__JSReadableStreamSource__load(lexicalGlobalObject);
    }
    }

#if BUN_DEBUG
    // in release, it is most likely that a negative int will be hit,
    // and a segfault will happen instead of this message.
    //
    // that is ok considering we do not expose this function to the public
    CRASH_WITH_INFO("Invalid call to @native. If you aren't calling this directly then bug @paperdave as they made a mistake in the code generator");
#else
    CRASH_WITH_INFO("Invalid call to @native. This should never be reached and is a bug in Bun or you got a handle to our internal code.");
#endif
}

} // namespace JS2Native
} // namespace Bun