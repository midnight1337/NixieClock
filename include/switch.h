#include "switch_base.h"



class SwitchMenu : public SwitchBase
{
    public:
        SwitchMenu(int pin);
        virtual void function() override;
};

class SwitchNext : public SwitchBase
{

    public:
        SwitchNext(int pin);
        virtual void function() override;
};

class SwitchPrevious : public SwitchBase
{

    public:
        SwitchPrevious(int pin);
        virtual void function() override;
};