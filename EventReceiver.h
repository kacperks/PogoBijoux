#ifndef EVENT_RECEIVER_H
#define EVENT_RECEIVER_H

class EventReceiver : public irr::IEventReceiver
{
    public:
        virtual bool OnEvent(const irr::SEvent& event)
        {
            if(event.EventType == irr::EET_KEY_INPUT_EVENT)
            {
                keyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
            }

            else if(event.EventType == irr::EET_MOUSE_INPUT_EVENT)
            {
                if(event.MouseInput.Event == irr::EMIE_LMOUSE_PRESSED_DOWN)
                {
                    mouseIsDown = true;
                }

                else if(event.MouseInput.Event == irr::EMIE_LMOUSE_LEFT_UP)
                {
                    mouseIsDown = false;
                }
            }

            return false;
        }

        virtual bool isKeyDown(irr::EKEY_CODE keyCode) const
        {
            return keyIsDown[keyCode];
        }

        virtual bool isMouseDown()
        {
            return mouseIsDown;
        }

        EventReceiver()
        {
            for(irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; i++)
            {
                keyIsDown[i] = false;
            }
        }

    private:
        bool mouseIsDown;
        bool keyIsDown[irr::KEY_KEY_CODES_COUNT];
};
#endif
