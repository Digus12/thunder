#include "bindings/angelbindings.h"

#include <angelscript.h>

#include <input.h>

void registerInput(asIScriptEngine *engine) {
    engine->SetDefaultNamespace("Input");

    engine->RegisterGlobalFunction("bool isKey(int)", asFUNCTION(Input::isKey), asCALL_CDECL);
    engine->RegisterGlobalFunction("bool isKeyDown(int)", asFUNCTION(Input::isKeyDown), asCALL_CDECL);
    engine->RegisterGlobalFunction("bool isKeyUp(int)", asFUNCTION(Input::isKeyUp), asCALL_CDECL);

    engine->RegisterGlobalFunction("bool isMouseButton()", asFUNCTION(Input::isMouseButton), asCALL_CDECL);
    engine->RegisterGlobalFunction("bool isMouseButtonDown(int)", asFUNCTION(Input::isMouseButtonDown), asCALL_CDECL);
    engine->RegisterGlobalFunction("bool isMouseButtonUp(int)", asFUNCTION(Input::isMouseButtonUp), asCALL_CDECL);

    engine->RegisterGlobalFunction("Vector4 mousePosition()", asFUNCTION(Input::mousePosition), asCALL_CDECL);
    engine->RegisterGlobalFunction("Vector4 mouseDelta()", asFUNCTION(Input::mouseDelta), asCALL_CDECL);
    engine->RegisterGlobalFunction("void setMousePosition(int, int)", asFUNCTION(Input::setMousePosition), asCALL_CDECL);

    engine->RegisterGlobalFunction("int joystickCount()", asFUNCTION(Input::joystickCount), asCALL_CDECL);
    engine->RegisterGlobalFunction("int joystickButtons(int)", asFUNCTION(Input::joystickButtons), asCALL_CDECL);
    engine->RegisterGlobalFunction("Vector4 joystickThumbs(int)", asFUNCTION(Input::joystickThumbs), asCALL_CDECL);
    engine->RegisterGlobalFunction("Vector2 joystickTriggers(int)", asFUNCTION(Input::joystickTriggers), asCALL_CDECL);

    engine->RegisterGlobalFunction("int touchCount()", asFUNCTION(Input::touchCount), asCALL_CDECL);
    engine->RegisterGlobalFunction("int touchState(int)", asFUNCTION(Input::touchState), asCALL_CDECL);
    engine->RegisterGlobalFunction("Vector4 touchPosition(int)", asFUNCTION(Input::touchPosition), asCALL_CDECL);

    engine->SetDefaultNamespace("");
}
