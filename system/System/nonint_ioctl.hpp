/*
 * nonint_ioctl.hpp
 *
 * non-interruptable ioctl() - continues if interrupt
 * coused returning error from call
 *
 */
#ifndef INCLUDE_SYSTEM_NONINT_IOCTL_HPP_FILE
#define INCLUDE_SYSTEM_NONINT_IOCTL_HPP_FILE

/* public header */

namespace System
{

int nonint_ioctl(int fd, int req, void *data);

} // namespace System

#endif

