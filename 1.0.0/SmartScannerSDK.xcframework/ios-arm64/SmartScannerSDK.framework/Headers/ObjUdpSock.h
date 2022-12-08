//
//  ObjUdpSock.h
//  SamLanDiscovery
//
//  Created by Menny-A on 08/11/2021.
//

#import <Foundation/Foundation.h>

#include <stdio.h>
#include <string.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/file.h>
#include <fcntl.h>
#include <net/if.h>
#include <ifaddrs.h>
#import <dns_sd.h>

//#import "SamLanDiscovery-Swift.h"

NS_ASSUME_NONNULL_BEGIN
typedef void (^ReciveDataCompletion)(NSData* data,char* str,short port);
@interface ObjUdpSock : NSObject{
    int sfd;
    short _port;
    struct sockaddr_in addr;
}
@property (copy, nonatomic) ReciveDataCompletion reciveDataCompletion;
- (id)initWithPort:(unsigned short)port;
-(void)close;
-(void)createUdpSocket;
- (void)reciveDataFromSocket:(void (^)(NSData* data,char* str,short port))finishBlock;
//-(MdnsData*)reciveDataFromSocket;
-(int)getSocket;
//-(void)sendDataOnNetworkQueue:(NSData *)packet:(NSString)ip:(short)port;
-(void)sendDataOnNetworkQueue:(NSData *)packet ipV4:(NSString *)ip andPort:(short)port;
+(NSArray*)getSubnet;
@property BOOL shouldContinue;

@end

NS_ASSUME_NONNULL_END
