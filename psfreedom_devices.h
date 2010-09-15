/*
 * psfreedom_devices.h -- PS3 Jailbreak exploit Gadget Driver
 *
 * Copyright (C) Youness Alaoui (KaKaRoTo)
 *
 * This software is distributed under the terms of the GNU General Public
 * License ("GPL") version 3, as published by the Free Software Foundation.
 *
 * This code is based in part on:
 * PSGroove
 *
 */

#include "bins/default_shellcode.h"
#include "bins/default_payload.h"

#define MAGIC_NUMBER		0x50, 0x53, 0x46, 0x72, 0x65, 0x65, 0x64, 0x6d

/* Hub endpoint Descriptor */
static struct usb_endpoint_descriptor jig_out_endpoint_desc = {
  .bLength =		USB_DT_ENDPOINT_SIZE,
  .bDescriptorType =	USB_DT_ENDPOINT,
  .bEndpointAddress =	USB_DIR_OUT | 0x02,
  .bmAttributes =	USB_ENDPOINT_XFER_BULK,
  .wMaxPacketSize =	__constant_cpu_to_le16(8),
  .bInterval =		0x00,
};

/* Hub endpoint Descriptor */
static struct usb_endpoint_descriptor jig_in_endpoint_desc = {
  .bLength =		USB_DT_ENDPOINT_SIZE,
  .bDescriptorType =	USB_DT_ENDPOINT,
  .bEndpointAddress =	USB_DIR_IN | 0x01,
  .bmAttributes =	USB_ENDPOINT_XFER_BULK,
  .wMaxPacketSize =	__constant_cpu_to_le16(8),
  .bInterval =		0x00,
};

static u8 jig_response[64] = {
  0x80, 0x00, 0x00, 0x00, 0x00, 0x3d, 0xee, 0x78,
  0x80, 0x00, 0x00, 0x00, 0x00, 0x3d, 0xee, 0x88,
  0x80, 0x00, 0x00, 0x00, 0x00, 0x33, 0xe7, 0x20,
};

static u8 port1_device_desc[] = {
  0x12, 0x01, 0x00, 0x02, 0x00, 0x00, 0x00, 0x08,
  0xAA, 0xAA, 0x55, 0x55, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x04,
};

static u8 port1_short_config_desc[] = {
  0x09, 0x02, 0x00, 0x0f, 0x01, 0x00, 0x00, 0x80,
};

static u8 port1_config_desc_prefix[] = {
  0x09, 0x02, 0x12, 0x00, 0x01, 0x00, 0x00, 0x80, 0xfa,
  0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, MAGIC_NUMBER
};

static u8 port2_device_desc[] = {
  0x12, 0x01, 0x00, 0x02, 0x00, 0x00, 0x00, 0x08,
  0xAA, 0xAA, 0xBB, 0xBB, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x01,
};

static u8 port2_config_desc[] = {
  // config
  0x09, 0x02, 0x16, 0x00, 0x01, 0x01, 0x00, 0x80,
  0x01,
  // interface
  0x09, 0x04, 0x00, 0x00, 0x00, 0xFE, 0x01, 0x02,
  0x00,
  // extra
  0x04, 0x21, 0xb4, 0x2f,
};

static u8 port3_device_desc[] = {
  0x12, 0x01, 0x00, 0x02, 0x00, 0x00, 0x00, 0x08,
  0xAA, 0xAA, 0x55, 0x55, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x02,
};


const u8 port0_device_desc[] = {
  0x50, 0x53, 0x46, 0x72, 0x65, 0x65, 0x64, 0x6f, 0x6d, 0x20, 0x62, 0x79, 0x20, 0x4b, 0x61, 0x4b,
  0x61, 0x52, 0x6f, 0x54, 0x6f, 0x0a, 0x52, 0x65, 0x6c, 0x65, 0x61, 0x73, 0x65, 0x64, 0x20, 0x75,
  0x6e, 0x64, 0x65, 0x72, 0x20, 0x47, 0x50, 0x4c, 0x20, 0x76, 0x33, 0x0a, 0x00, 0x00, 0x00, 0x00,
};

static u8 port3_config_desc[] = {
  0x09, 0x02, 0x4d, 0x0a, 0x01, 0x01, 0x00, 0x80, 0x01, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01,
  0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00,
  0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00,
  0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09,
  0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe,
  0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00,
  0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04,
  0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
  0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00,
  0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00,
  0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09,
  0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02,
  0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00,
  0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04,
  0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
  0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01,
  0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00,
  0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09,
  0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02,
  0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe,
  0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04,
  0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
  0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01,
  0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09,
  0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02,
  0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe,
  0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
  0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01,
  0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00,
  0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00,
  0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02,
  0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe,
  0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00,
  0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04,
  0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01,
  0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00,
  0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00,
  0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09,
  0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe,
  0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00,
  0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04,
  0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
  0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00,
  0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00,
  0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09,
  0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02,
  0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00,
  0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04,
  0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
  0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01,
  0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00,
  0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09,
  0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02,
  0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe,
  0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04,
  0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
  0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01,
  0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09,
  0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02,
  0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe,
  0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
  0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01,
  0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00,
  0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00,
  0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02,
  0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe,
  0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00,
  0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04,
  0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01,
  0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00,
  0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00,
  0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09,
  0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe,
  0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00,
  0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04,
  0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
  0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00,
  0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00,
  0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09,
  0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02,
  0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00,
  0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04,
  0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
  0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01,
  0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00,
  0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09,
  0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02,
  0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe,
  0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04,
  0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
  0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01,
  0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09,
  0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02,
  0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe,
  0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
  0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01,
  0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00,
  0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00,
  0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02,
  0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe,
  0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00,
  0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04,
  0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01,
  0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00,
  0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00,
  0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09,
  0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe,
  0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00,
  0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04,
  0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
  0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00,
  0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00,
  0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09,
  0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02,
  0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00,
  0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04,
  0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
  0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01,
  0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00,
  0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09,
  0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02,
  0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe,
  0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04,
  0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
  0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01,
  0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09,
  0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02,
  0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe,
  0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
  0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01,
  0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00,
  0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00,
  0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02,
  0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe,
  0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00,
  0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04,
  0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01,
  0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00,
  0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00,
  0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09,
  0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe,
  0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00,
  0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04,
  0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
  0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00,
  0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00,
  0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09,
  0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02,
  0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00,
  0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04,
  0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
  0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01,
  0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00,
  0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09,
  0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02,
  0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe,
  0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02,
};

static u8 port4_device_desc[] = {
  0x12, 0x01, 0x00, 0x02, 0x00, 0x00, 0x00, 0x08,
  0xAA, 0xAA, 0x55, 0x55, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x03,
};

static u8 port4_config_desc_1[] = {
  // config
  0x09, 0x02, 0x12, 0x00, 0x01, 0x01, 0x00, 0x80,
  0x01,
  // interface
  0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02,
  0x00,
};

static u8 port4_short_config_desc_2[] = {
  // config
  0x09, 0x02, 0x12, 0x00, 0x01, 0x01, 0x00, 0x80,
};

static u8 port4_config_desc_2[] = {
  // config
  0x09, 0x02, 0x00, 0x00, 0x01, 0x01, 0x00, 0x80,
  0x01,
  // interface
  0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02,
  0x00,
};

static u8 port4_config_desc_3[] = {
  0x09, 0x02, 0x30, 0x00, 0x01, 0x01, 0x00, 0x80, 0x01, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01,
  0x02, 0x00, 0x3e, 0x21, 0x00, 0x00, 0x00, 0x00, MAGIC_NUMBER,
  0x80, 0x00, 0x00, 0x00, 0x00, 0x46, 0x50, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x3d, 0xee, 0x70,
};

static u8 port5_device_desc[] = {
  0x12, 0x01, 0x00, 0x02, 0x00, 0x00, 0x00, 0x08,
  0x4c, 0x05, 0xeb, 0x02, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x01,
};

static u8 port5_config_desc[] = {
  // config
  0x09, 0x02, 0x20, 0x00, 0x01, 0x01, 0x00, 0x80,
  0x01,
  // interface
  0x09, 0x04, 0x01, 0x00, 0x02, 0xff, 0x00, 0x00,
  0x00,
  // endpoint
  0x07, 0x05, 0x02, 0x02, 0x08, 0x00, 0x00,
  // endpoint
  0x07, 0x05, 0x81, 0x02, 0x08, 0x00, 0x00,
};

static u8 port6_device_desc[] = {
  0x12, 0x01, 0x00, 0x02, 0x00, 0x00, 0x00, 0x08,
  0xaa, 0xaa, 0xc0, 0xde, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x01,
};

static u8 port6_config_desc[] = {
  // config
  0x09, 0x02, 0x12, 0x00, 0x01, 0x01, 0x00, 0x80,
  0x01,
  // interface
  0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02,
  0x00,
};


