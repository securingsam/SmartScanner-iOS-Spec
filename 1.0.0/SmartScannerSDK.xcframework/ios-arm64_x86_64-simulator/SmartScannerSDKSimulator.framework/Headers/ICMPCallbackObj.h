//
//  ICMPCallbackObj.h
//  ScanLib
//
//  Created by Menny_A_Ios on 06/06/2022.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN
typedef void (^icmp_block)(struct in_addr ip, int ttl);

@interface ICMPCallbackObj : NSObject
    @property (copy, nonatomic) icmp_block reciveDataCompletion;
@end

NS_ASSUME_NONNULL_END
