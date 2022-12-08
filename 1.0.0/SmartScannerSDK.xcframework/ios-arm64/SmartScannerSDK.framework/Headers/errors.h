/*
 * This file is (c) 2016, 2017, 2018, 2019 Securing SAM Ltd.
 *
 * It may not be reproduced, used, sold or transferred to any third party
 * without the prior written consent of Securing SAM Ltd. All rights reserved.
 */

/**
 * @brief Internal SAM errors for use in most functions.
 * @file errors.h
 *
 * @author Omri Mallis
 * @date 27 March 2016
 */
#ifndef __SAM_ERRORS_H__
#define __SAM_ERRORS_H__

typedef enum {
    SAM_OK = 0,         /* Success. */
    SAM_EFAILURE,       /* Generic failure code. */
    SAM_ENOENT,         /* No such file or directory. */
    SAM_EAGAIN,         /* Try again. */
    SAM_EWOULDBLOCK,    /* Operation cannot be completed immediately. */
    SAM_ENOMEM,         /* Out of memory. */
    SAM_EEXIST,         /* File exists. */
    SAM_EINVAL,         /* Invalid argument. */
    SAM_ECHILD,         /* No child processes. */
    SAM_E2BIG,          /* Argument list too long. */
    SAM_ENOSYS,         /* Not implemented. */
    SAM_ENETUNREACH,    /* Network is unreachable. */
    SAM_ETIMEDOUT,      /* Connection timed out. */
    SAM_ECONNREFUSED,   /* Connection refused. */
    SAM_EACCES,         /* Access denied. */
    SAM_ENOTSUP,        /* Not Supported. */
    SAM_EPROTOTYPE,     /* Wrong protocol. */
    SAM_EPARSE,         /* Parsing error. */
    SAM_ESERVER,        /* Server returned error. */
    SAM_EXTABLES,       /* Error in iptables/ebtables/etc. */
    SAM_ENETLINK,       /* Error in netlink library. */
    SAM_EMONGOOSE,      /* Error in mongoose library. */
    SAM_ELMDB,          /* Error in lmdb library. */
    SAM_EHOSTAPD,       /* Error in hostapd library. */
    SAM_ENOINS,         /* Sam doesn't have a license */
    SAM_NOCHG,          /* There are no changes -> for diff loops */
    SAM_EDBUS,          /* D-Bus related error */
    SAM_EHTP,           /* Lib htp related error */
    SAM_EIPSET,         /* IPSet related error */
    SAM_ECONNRESET      /* Connection has been reset by the peer */
} sam_errno_t;

/**
 * @brief Convert system error (errno) to sam internal error code.
 *
 * @return One of sam_errno_t;
 */
int sam_syserr2samerr(int err);

#endif /* end of include guard: __SAM_ERRORS_H__ */
