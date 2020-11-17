//
//  ZYOpenAccountSDK.h
//  ZYIOTSDK
//
//  Created by ZYIT_cxm on 2018/11/21.
//  Copyright © 2018年 cxm. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ZYDevUpdateDelegate.h"

#import "ZYBaseSDK.h"


/**APP使用第三方用户自有用户系统接入SDK时使用本ZYOpenAccountSDK。（不能与ZYAccountSDK同时使用，不兼容）*/
@interface ZYOpenAccountSDK :ZYBaseSDK

/**
 初始化SDK
 @param tenantId ZY提供的TenantID
 @param appId ZY提供的APP ID
 @param appSecret ZY提供的APP Secret
 @param appToken 第三方用户登录自有用户系统的token
 @param server 服务器IP或域名
 @param handler 回调（使用ZYOpenAccount时，返回的userToken信息userId字段为空。）
 @return ZYOpenAccountSDK 实例
 */
+(instancetype) initZYOpenAccountSDKWithTenantId:(int )tenantId appId:(NSString *)appId appSecret:(NSString *)appSecret appToken:(NSString *)appToken server:(NSString *)server  completion:(void (^)(ZYUserToken *uToken,int retcode ,NSString *errDescription)) handler;

/**
 初始化SDK
 @param tenantId ZY提供的TenantID
 @param appId ZY提供的APP ID
 @param appSecret ZY提供的APP Secret
 @param appToken 第三方用户登录自有用户系统的token
 @param handler 回调（使用ZYOpenAccount时，返回的userToken信息userId字段为空。）
 @return ZYOpenAccountSDK 实例
 */
+(instancetype) initZYOpenAccountSDKWithTenantId:(int )tenantId appId:(NSString *)appId appSecret:(NSString *)appSecret appToken:(NSString *)appToken completion:(void (^)(ZYUserToken *uToken,int retcode ,NSString *errDescription)) handler;


/**
 获取接口实例
 @return ZYOpenAccountSDK
 */
+(instancetype) getZYOpenAccountSDKInstance;

/**
 set UserInfo
 参数：
 可选参数：(传入要设置的值，其余值置空（nil）即可)
 msgSwitch：消息推送开关（true或false）
 pushSwitch：推送总开关（true或false）
 emailSwitch：邮箱推送总开关（true或false）
 wechatSwitch：微信推送总开关（true或false）
 phonePush：手机推送（ios_1表示发布推送，ios_0表示开发推送）
 channelId：推送通道id（ios推送时对应的deviceToken）
 noDisturbTime：消息免打扰时间（以秒为单位（一天内的秒数值，范围是0到86400），中间用‘-’隔开，如：12345-34567；如果结束时间小于起始时间，说明包含是第二天的一段时间）
 headProtrait：头像路径（文件名或http url）
 ring：个性铃声（文件名——只允许筑云指定文件）
 language：语言（zh中文，en英文）
 fontSize：字体大小（数值）
 personalInfo：个人信息（预留）
 注：不需要用户昵称，用户昵称登录时由第三方后台提供。
 handler: callback
 */
-(void) openSetUserInfoWithMsgSwitch:(NSString *) msgSwitch pushSwitch:(NSString *) pushSwitch emailSwitch:(NSString *)emailSwitch wechatSwitch:(NSString *)wechatSwitch phonePush:(NSString *)phonePush channelId:(NSString *) channelId noDisturbTime:(NSString *)noDisturbTime headProtrait:(NSString *) headProtrait ring:(NSString *)ring language:(NSString *)language fontSize:(NSString *)fontSize personalInfo:(NSString *)personalInfo    completion:(void (^)( int retcode ,NSString *errDescription)) handler;


/**
 获取用户信息
 返回的User信息userId字段指的是第三方用户Id，不是zotUserId。
 */
-(void)openGetUserInfoWithCompletion:(void (^)(ZYUser *user,int retcode ,NSString *errDescription)) handler;


/**
 解除微信公众号绑定(会收不到微信推送) 
 @param handler callback
 */
-(void) openWechatRemovePublicWithCompletion:(void (^)(int retcode ,NSString *errDescription)) handler ;



/** 一级用户授权给二级用户
 参数：
 keyhash device
 authUserId：被授权用户Id，为第三方系统的用户Id。
 authority：用户控制权限，json数据。
 remark：备注
 注：1.  未购买历史记录套餐，二级授权最高5个，购买历史记录套餐，最高19个。
 授权二级用户需要推送和存储log记录。
 authority: json格式数据，type：操控类型，0表示全时访问，无需time和week；1表示时段访问，无需week；2表示定期访问。time表示操控时间，如果是时段访问，内容为起始-结束时间戳（单位是秒），中间用-分割；如果是定期访问，内容为当天时间的起始秒-结束秒（范围：0到86400，24小时制 ，如上午8点对应的秒数是28800），中间用-分割。week表示星期，1-7分别表示周一到周日，如：137表示周一周三周日。shareTime表示分享时间，为时间戳。形如：{"type":"2","time":"12345-23456","week":"127","shareTime":"1456789220"}
 handler: callback
 */
-(void) openAuthorizeUserWithKeyhash:(NSString*)keyhash authUserId:(NSString*)authUserId authority:(AuthorityEntity*)authority remark:(NSString*)remark completion:(void (^)( int retcode ,NSString *errDescription)) handler;


/**
 一级用户修改二级用户权限
 参数：
 keyhash
 authUserId：授权用户Id，为第三方userId
 authority：用户控制权限，json数据。详见授权API中authority字段参数的描述。
 remark：备注
 handler :callback
 */
-(void)openModifyAuthUserWithKeyhash:(NSString*)keyhash authUserId:(NSString*)authUserId authority:(AuthorityEntity*)authority remark:(NSString*)remark completion:(void (^)( int retcode ,NSString *errDescription)) handler;

/**
 一级用户解授权二级用户
 参数：
 keyhash device
 authUserId：授权用户Id，为第三方userId
 */
-(void) openUnAuthorizeUserWithKeyhash:(NSString*)keyhash authUserId:(NSString*)authUserId completion:(void (^)(int retcode ,NSString *errDescription)) handler;


/**
 获取设备所属的用户列表（包括管理员、二级用户、临时用户）
 @param keyhash device
 @param handler  callback array:ZYUser
 */
-(void) openGetUserListWithKeyhash:(NSString*)keyhash completion:(void (^)(NSMutableArray *users, NSMutableArray *tempUsers,int retcode ,NSString *errDescription)) handler;





@end
