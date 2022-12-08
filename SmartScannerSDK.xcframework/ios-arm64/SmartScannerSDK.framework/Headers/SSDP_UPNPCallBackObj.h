//
//  SSDP_UPNPCallBackObj.h
//  ScanLib
//
//  Created by Menny_A_Ios on 08/06/2022.
//


#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN
typedef void (^ssdp_block)(NSData* data, struct in_addr ip,int32_t port);
typedef void (^upnp_block)(int32_t port,struct in_addr  ip,NSData*  data);
typedef void (^mdns_block)(NSData* data, struct in_addr ip,int32_t port);
@interface SSDP_UPNPCallBackObj : NSObject
    @property (copy, nonatomic) ssdp_block receiveSSdpDataCompletion;
    @property (copy, nonatomic) upnp_block receiveUpnpDataCompletion;
    @property (copy, nonatomic) mdns_block receiveDialsDataCompletion;
@end

NS_ASSUME_NONNULL_END
