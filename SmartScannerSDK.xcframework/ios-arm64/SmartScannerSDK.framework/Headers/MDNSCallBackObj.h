//
//  MDNSCallBackObj.h
//  ScanLib
//
//  Created by Menny_A_Ios on 08/06/2022.
//


#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN
typedef void (^mdns_block)(NSData* data, struct in_addr ip,int32_t port);

@interface MDNSCallBackObj : NSObject
    @property (copy, nonatomic) mdns_block receiveMdnsDataCompletion;
@end

NS_ASSUME_NONNULL_END
