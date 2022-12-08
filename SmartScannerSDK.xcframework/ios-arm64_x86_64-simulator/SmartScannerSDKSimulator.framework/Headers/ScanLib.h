//
//  ScanLib.h
//  ScanLib
//
//  Created by Menny_A_Ios on 30/03/2022.
//

#import <Foundation/Foundation.h>
#import "BannerGrabCallbackObj.h"
#import "ICMPCallbackObj.h"
#import "MDNSCallBackObj.h"
#import "SSDP_UPNPCallBackObj.h"
#import "DialCallBack.h"
#import "NetBiosCallBackObj.h"
#import "DNSCallBackObj.h"


@interface ScanLib : NSObject

//MARK: - initial's param for multi threads evetn loops
-(void)startScannerWithIP:(char *)ip;


//MARK: - OBJC callbacks initials


//MARK: - RUN SCANNERS METHODs
-(void)scanICMPWithIP:(char *)ip andSubnetMask:(char *)subnet andIgnoreIp:(char*[]) arr withSize:(int) size withCompletion:(ICMPCallbackObj *)handler;
-(void)scannBannerGrabbingForIp:(char *)ip withCompletion:(BannerGrabCallbackObj *)handler;
-(void)scanMDNSWithCompletion:(MDNSCallBackObj *)handler;
-(void)scanSSDPWithCompletion:(SSDP_UPNPCallBackObj *)handler;
-(void)scanHostNamesWithIP:(char *)ip andSubnetMask:(char *)subnet andIgnoreIp:(char*[]) arr withSize:(int) size withCompletion:(MDNSCallBackObj *)handler;
-(void)scanDnsHostNamesWithIP:(char *)ip andSubnetMask:(char *)subnet gateWayIp:(char *)gateWay andIgnoreIp:(char*[]) arr withSize:(int) size withCompletion:(DNSCallBackObj *)handler;
-(void)scanNetBiosWith:(char *)subnet andIgnoreIp:(char*[]) arr withSize:(int) size withCompletion:(NetBiosCallBackObj *)handler ;
//MARK: - Closse methods
///close all event loop after that it will not ali
-(void)closeScanner;
-(void)closeSeperateScanners;
-(void)sendMsearchithIP:(char *)ip;
-(void)sendMsearchMultiCast;

typedef void (^LogerBlock)(NSData* data);
- (void) initLogerwithCompletion:(LogerBlock)handler;
@end

