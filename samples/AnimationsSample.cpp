// Copyright (C) 2018 Elviss Strazdins
// This file is part of the Ouzel engine.

#include "AnimationsSample.hpp"
#include "MainMenu.hpp"

using namespace std;
using namespace ouzel;

AnimationsSample::AnimationsSample():
    backButton("button.png", "button_selected.png", "button_down.png", "", "Back", "arial.fnt", 1.0f, Color::BLACK, Color::BLACK, Color::BLACK)
{
    eventHandler.gamepadHandler = bind(&AnimationsSample::handleGamepad, this, placeholders::_1, placeholders::_2);
    eventHandler.uiHandler = bind(&AnimationsSample::handleUI, this, placeholders::_1, placeholders::_2);
    eventHandler.keyboardHandler = bind(&AnimationsSample::handleKeyboard, this, placeholders::_1, placeholders::_2);
    engine->getEventDispatcher()->addEventHandler(&eventHandler);

    camera.setScaleMode(scene::Camera::ScaleMode::SHOW_ALL);
    camera.setTargetContentSize(Size2(800.0f, 600.0f));
    cameraActor.addComponent(&camera);
    layer.addChild(&cameraActor);
    addLayer(&layer);

    shapeDrawable.rectangle(ouzel::Rect(100.0f, 100.0f), Color(0, 128, 128, 255), true);
    shapeDrawable.rectangle(ouzel::Rect(100.0f, 100.0f), Color::WHITE, false, 2.0f);
    shapeDrawable.line(Vector2(0.0f, 0.0f), Vector2(50.0f, 50.0f), Color::CYAN, 2.0f);

    shapeDrawable.curve({Vector2(50.0f, 50.0f),
                         Vector2(100.0f, 50.0f),
                         Vector2(50.0f, 0.0f),
                         Vector2(100.0f, 0.0f)},
                        Color::YELLOW);

    shapeDrawable.circle(Vector2(25.0f, 75.0f), 20.0f, Color::BLUE, true);
    shapeDrawable.circle(Vector2(25.0f, 75.0f), 20.0f, Color::WHITE, false);
    shapeDrawable.circle(Vector2(75.0f, 75.0f), 20.0f, Color::BLUE, false, 16, 4.0f);

    shapeDrawable.polygon({Vector2(15.0f, 75.0f),
                           Vector2(25.0f, 75.0f),
                           Vector2(25.0f, 55.0f)},
                          Color("#ff0000"), false);

    drawActor.addComponent(&shapeDrawable);
    drawActor.setPosition(Vector2(-300, 0.0f));
    layer.addChild(&drawActor);

    shake.reset(new scene::Shake(10.0f, Vector2(10.0f, 20.0f), 20.0f));
    drawActor.addComponent(shake);
    shake->start();

    witchSprite.init("witch.png");

    witch.setPosition(Vector2(200, 0.0f));
    witch.addComponent(&witchSprite);
    layer.addChild(&witch);

    witchScale.reset(new scene::Scale(2.0f, Vector2(0.1f, 0.1f), false));
    witchFade.reset(new scene::Fade(2.0f, 0.4f));

    vector<scene::Animator*> parallel = {
        witchScale.get(),
        witchFade.get()
    };

    witchRotate.reset(new scene::Rotate(1.0f, Vector3(0.0f, 0.0f, TAU), false));

    witchRepeat.reset(new scene::Repeat(witchRotate, 3));
    witchParallel.reset(new scene::Parallel(parallel));

    vector<scene::Animator*> sequence = {
        witchRepeat.get(),
        witchParallel.get()
    };

    witchSequence.reset(new scene::Sequence(sequence));

    witch.addComponent(witchSequence);
    witchSequence->start();

    ballSprite.init("ball.png");

    ball.addComponent(&ballSprite);
    layer.addChild(&ball);

    ballDelay.reset(new scene::Animator(1.0f));
    ballMove.reset(new scene::Move(2.0f, Vector2(0.0f, -240.0f), false));
    ballEase.reset(new scene::Ease(ballMove, scene::Ease::Type::EASE_OUT, scene::Ease::Func::BOUNCE));

    vector<scene::Animator*> sequence2 = {
        ballDelay.get(),
        ballEase.get()
    };

    ballSequence.reset(new scene::Sequence(sequence2));

    ball.addComponent(ballSequence);
    ballSequence->start();

    guiCamera.setScaleMode(scene::Camera::ScaleMode::SHOW_ALL);
    guiCamera.setTargetContentSize(Size2(800.0f, 600.0f));
    guiCameraActor.addComponent(&guiCamera);
    guiLayer.addChild(&guiCameraActor);
    addLayer(&guiLayer);

    guiLayer.addChild(&menu);

    backButton.setPosition(Vector2(-200.0f, -200.0f));
    menu.addWidget(&backButton);
}

bool AnimationsSample::handleGamepad(Event::Type type, const GamepadEvent& event)
{
    if (type == Event::Type::GAMEPAD_BUTTON_CHANGE)
    {
        if (event.pressed &&
            event.button == input::GamepadButton::FACE_RIGHT)
        {
            engine->getSceneManager()->setScene(std::unique_ptr<scene::Scene>(new MainMenu()));
        }
    }

    return true;
}

bool AnimationsSample::handleUI(Event::Type type, const UIEvent& event) const
{
    if (type == Event::Type::ACTOR_CLICK && event.actor == &backButton)
    {
        engine->getSceneManager()->setScene(std::unique_ptr<scene::Scene>(new MainMenu()));
    }

    return true;
}

bool AnimationsSample::handleKeyboard(Event::Type type, const KeyboardEvent& event) const
{
    if (type == Event::Type::KEY_PRESS)
    {
        switch (event.key)
        {
            case input::KeyboardKey::ESCAPE:
            case input::KeyboardKey::MENU:
                engine->getSceneManager()->setScene(std::unique_ptr<scene::Scene>(new MainMenu()));
                break;
            default:
                break;
        }
    }

    return true;
}
