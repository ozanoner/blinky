
#include "app_bsp.h"
#include "FreeAct.h"
#include "esp_log.h"

#define TAG "app"

typedef struct
{
    Active super;
    TimeEvent te;
} Blinky;

static Blinky blinky;
static StackType_t blinky_stack[configMINIMAL_STACK_SIZE * 2];
static Event *blinky_queue[10];

static void Blinky_ctor(Blinky *const me);
static void Blinky_dispatch(Blinky *const me, Event const *const e);

void app_main()
{
    ESP_LOGI(TAG, "Example start");
    AppBSP_init();

    Blinky_ctor(&blinky);
    Active_start(&blinky.super,
                 1, // priority
                 blinky_queue, sizeof(blinky_queue) / sizeof(blinky_queue[0]),
                 blinky_stack, sizeof(blinky_stack),
                 0 // options
    );
}

static void Blinky_ctor(Blinky *const me)
{
    Active_ctor(&me->super, (DispatchHandler)&Blinky_dispatch);
    me->te.type = TYPE_PERIODIC;
    TimeEvent_ctor(&me->te, USER_SIG, &me->super);
}

static void Blinky_dispatch(Blinky *const me, Event const *const e)
{
    ESP_LOGI(TAG, "Blinky_dispatch: sig=%d", e->sig);

    switch (e->sig)
    {
    case INIT_SIG:
        TimeEvent_arm(&me->te, 3000);
        break;

    case USER_SIG:
        AppBSP_toggle_red();
        AppBSP_toggle_blue();
        break;

    default:
        break;
    }
}
