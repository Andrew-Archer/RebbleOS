#pragma once
/**
 * @file notification_manager_c.h
 * @author Barry Carter
 * @date 12 Feb 2018
 * @brief Notification Windows. Allows you to pop a structured notification over content
 *
 * A notification window will create an \ref OverlayWindow and 
 * inject the relevant subcontent. 
 */
#include "overlay_manager.h"
#include "notification_layer.h"
#include "protocol_notification.h"
#include "notification_message.h"
#include "timeline.h"

/**
 * @brief When we are in a notification and a button is pressed, 
 * how long to rearm the timer for. it has to go away eventually 
 */
#define REARM_TIMEOUT_MS 30000

/* internal init */
uint8_t notification_init(void);

/**
 * @brief Show a fullscreen message. Or if already visible, show the new message
 * 
 * @param msuuid \ref Uuid the uuid of the new message
 */
void notification_arrived(Uuid *uuid);

/**
 * @brief Show a battery overlay. Shows current battery status
 * 
 * @param timeout_ms Time in ms before we auto close the window. 0 is disabled
 */
void notification_show_battery(uint32_t timeout_ms);

/**
 * @brief Show a small overlayed box that is not fullscreen.
 * 
 * @note default timeout is 5000ms
 * @param message a char of the message to show.
 * @param frame \ref GRect the size and position of the window
 */
void notification_show_small_message(const char *message, GRect frame);
void notification_show_incoming_call(const char *caller);
void notification_show_alarm(uint8_t alarm_id);
void notification_window_dismiss();

/**
 * @brief Apply the click configuraion to the notifcation window.
 * 
 * @param app_window the running application \ref Window that we want to override
 */
void notification_load_click_config(Window *app_window);

/* Internal implementation */
void notification_message_display(OverlayWindow *overlay, Window *window);
void battery_overlay_display(OverlayWindow *overlay, Window *window);
void battery_overlay_destroy(OverlayWindow *overlay, Window *window);
void mini_message_overlay_display(OverlayWindow *overlay, Window *window);
void mini_message_overlay_destroy(OverlayWindow *overlay, Window *window);
void notification_reschedule_timer(Window *window, uint32_t timeout_ms);

typedef struct notification_data_t {
    OverlayCreateCallback create_callback;
    OverlayCreateCallback destroy_callback;
    OverlayWindow *overlay_window;
    AppTimerHandle timer;
    uint32_t timeout_ms;
} notification_data;

typedef struct notification_message_t {
    notification_data data;
    NotificationLayer *notification_layer;
    Uuid *uuid;
} notification_message;

typedef struct notification_battery_t {
    notification_data data;
} notification_battery;

typedef struct notification_mini_msg_t {
    notification_data data;
    char *message;
    uint16_t icon;
    GRect frame;
} notification_mini_msg;
