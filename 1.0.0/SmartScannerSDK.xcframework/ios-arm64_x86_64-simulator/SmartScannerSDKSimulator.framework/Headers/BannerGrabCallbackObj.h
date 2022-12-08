//
//  SomeDevice.h
//  ScanLib
//
//  Created by Menny_A_Ios on 02/06/2022.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef void (^bannerGrab_block)(int32_t port, struct in_addr ip, NSData *data, char *_Nullable user_data);

@interface BannerGrabCallbackObj: NSObject
    @property (nonatomic, copy) NSString *deviceMac;
    @property (nonatomic, copy) NSString *deviceID;
    @property (copy, nonatomic) bannerGrab_block reciveDataCompletion;
@end

NS_ASSUME_NONNULL_END
