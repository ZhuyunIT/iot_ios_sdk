//
//  FotaAPI.h
//  ZYIOTSDK
//
//  Created by ZYIT_cxm on 2018/11/27.
//  Copyright © 2018年 ZYIT All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ZYDevUpdateDelegate.h"

@interface ZYFotaAPI : NSObject
/**获取接口实例*/
+(instancetype)getFotaInstance;

/**获取接口实例，并建立连接*/
+(instancetype)getFotaInstanceWithOpenConnection;

/**获取连接的状态，调用接口前请先判断状态，并进行相应操作。
 1是正常连接可以调用接口，2是异常需要重新openConnection后重试，0是无状态需要openConnection*/
-(int)connectStatus;

/**设置Fota模块的域名或IP，只能一个IP或域名*/
-(void)setFotaDomain:(NSString *) domain;

/**设置Fota模块的端口号*/
-(void)setFotaPort:(int) port;

/**
  连接服务器
 */
- (void)openConnection ;

/**
  停止连接
 */
- (void)shutdown;

/**实现接口可以得到检测版本结果和升级进度
 @param delegate 回调接口
 */
-(void)setDevUpdateWithDelegate:(id<ZYDevUpdateDelegate>) delegate keyhash:(NSString *)keyhash;

/**检测设备是否需要升级
 */
-(void) checkDevUpdateVersion  ;

/**
 发送event通知设备升级
 @return 返回eventId数值则表示已发送，具体发送Event的结果请实现ZYEventResponseDelegate代理监听
 */
-(NSString *) setDevUpdateStart;


/** 获取设备升级的进度
 */
-(void) getDevUpdateProgress  ;

 
@end
