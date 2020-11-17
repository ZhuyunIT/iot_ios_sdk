//
//  ZYDevUpdateDelegate.h
//  ZYIOTSDK
//
//  Created by ZYIT_cxm on 2018/11/27.
//  Copyright © 2018年 ZYIT All rights reserved.
//

#ifndef ZYDevUpdateDelegate_h
#define ZYDevUpdateDelegate_h


#endif /* ZYDevUpdateDelegate_h */
 
@protocol ZYDevUpdateDelegate

/**
 @param retcode 1-ok, 0-exp(keyhash not found)
 @param isNewest true-isNewest, false-need to update
 @param isForceUpdate true-need update(不升级无法正常使用),false-不是强制升级
 @param currentV 设备当前版本
 @param newestV 设备最新版本
 */
-(void) callCheckDevUpdateWithRetcode:(int16_t)retcode keyhash:(NSString *) keyhash isNewest:(BOOL) isNewest isForceUpdate:(BOOL) isForceUpdate currentVer:(NSString *)currentV newestVer:(NSString *)newestV;

/**get device update progress
 @param keyhash device
 @param progress  update progress
 */
-(void) callGetDevUpdateProgressWithRetcode:(int16_t)retcode keyhash:(NSString *) keyhash progress:(int)progress;


-(void) onCloseConnectToFota;
@end
