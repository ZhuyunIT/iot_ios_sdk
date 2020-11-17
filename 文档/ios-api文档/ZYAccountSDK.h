//
//  ZYAccountSDK.h
//  ZYIOTSDK
//
//  Created by ZYIT_cxm on 2018/11/21.
//  Copyright © 2019年 ZYIT All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ZYBaseSDK.h"


/**APP使用筑云用户系统接入SDK时使用本ZYAccountSDK。（不能与ZYOpenAccountSDK同时使用，不兼容）*/
@interface ZYAccountSDK : ZYBaseSDK  
+(instancetype) getZYAccountSDKInstance;


/** 用户使用手机或邮箱登录
 * @param tenantId tenantId
 * @param account   已注册筑云的手机或邮箱
 * @param password  筑云用户密码
 * @param phonePush 手机推送，android_0表示百度云推送，android_1表示gcm推送。
 * @param channelId 推送通道id
 * @param language  语言(中国zh，美国en)
 * @param handler  callback(ZYUserToken,retcode ,errDescription)
 */
-(void) loginWithTenantId:(int)tenantId account:(NSString *)account password:(NSString *)password phonePush:(PhonePushType ) phonePush  channelId:(NSString *)channelId language:(NSString *)language completion:(void (^)(ZYUserToken *token,int retcode ,NSString *errDescription)) handler;

/** 用户使用手机或邮箱登录
 * @param account   已注册筑云的手机或邮箱
 * @param password  筑云用户密码
 * @param phonePush 手机推送，android_0表示百度云推送，android_1表示gcm推送。
 * @param channelId 推送通道id
 * @param language  语言(中国zh，美国en)
 * @param handler  callback(ZYUserToken,retcode ,errDescription)
 */
-(void) loginWithAccount:(NSString *)account password:(NSString *)password phonePush:(PhonePushType ) phonePush  channelId:(NSString *)channelId language:(NSString *)language completion:(void (^)(ZYUserToken *token,int retcode ,NSString *errDescription)) handler  ;

/***获取注册验证码
 * 注：1.邮箱验证码有效期一个小时，短信验证码有效期3分钟
 2.密码只是验证码发送时带回作用，实际密码以用户注册api为准。
 * @param account 手机号或邮箱号
 * @param password 注册密码，会随验证码一起发送
 * @param handler callback(retcode,errDescription)
 */
-(void) getRegistVerifyWithAccount:(NSString *)account password:(NSString *)password completion:(void (^)(ZYUserVerifyResult *result,int retcode,NSString *errDescription))handler ;

/***
 *  注册用户
 * @param account 手机号或邮箱号
 * @param password 用户密码
 * @param verifyCode 收到的验证码
 * 以下三个是可选参数：
 * @param phonePush 手机接收推送的方式
 * @param channelId 推送通道id
 * @param language 指定接收推送内容的语言
 * @param handler callback(userToken,retcode,errDescription)
 */
-(void) registWithAccount:(NSString *)account password:(NSString *)password verifyCode:(NSString *)verifyCode phonePush:(PhonePushType )phonePush channelId:(NSString *)channelId language:(NSString *)language completion:(void (^)(ZYUserToken *token,int retcode,NSString *errDescription)) handler;


/***
 * 设置用户信息
 以下参数非必须全有，需设定的值有即可，其他值置空。
 *@param nickname ：昵称
 * @param msgSwitch ：消息推送开关
 * @param pushSwitch ：推送总开关
 * @param wechatSwitch ：微信推送总开关
 * @param phonePush ：手机推送
 * @param channelId ：推送通道id
 * @param noDisturbTime ：消息免打扰时间（以秒为单位，中间用‘-’隔开，如：12345-34567；如果结束时间小于起始时间，说明是第二天）
 * @param headProtrait ：头像路径
 * @param ring ：个性铃声
 * @param language ：语言（ZH中文，EN英文）
 * @param fontSize ：字体大小
 * @param personalInfo ：个人信息
 * @param handler  callback(retcode,errDescription)
 */
-(void) setUserInfoWithNickname:(NSString *)nickname msgSwitch:(NSString *)msgSwitch pushSwitch:(NSString *)pushSwitch wechatSwitch:(NSString *)wechatSwitch  phonePush:(PhonePushType)phonePush channelId:(NSString *)channelId noDisturbTime:(NSString *)noDisturbTime headProtrait:(NSString *)headProtrait ring:(NSString *)ring language:(NSString *)language fontSize:(int)fontSize personalInfo:(NSString *)personalInfo completion:(void (^)(int retcode,NSString *errDescription)) handler;

/***
 *获取用户信息
 * @param handler callback(userInfo,retcode,errDescription)
 */
-(void) getUserInfo:(void (^)(ZYUser *user,int retcode ,NSString *errDescription)) handler  ;

/***
 * 用户修改密码
 * @param oldPassword ：原密码
 * @param newPassword ：新密码
 * @param handler callback(retcode,errDescription)
 */
-(void) modifyPasswordWidthOldPassword:(NSString *)oldPassword newPassword:(NSString *)newPassword completion:(void (^)(int retcode,NSString *errDescription)) handler;

/***
 * 忘记密码：获取验证码
 * 注：1.如果有绑定邮箱，优先发送验证码到邮箱
 2.用于忘记密码，设置新密码。
 * @param account ：手机号或邮箱
 * @param password ：新设置的密码
 * @param handler callback(isEmailReceiver,smsRemain,account,retcode,errDescription)
 */
-(void) getForgetPwdVerifyWithAccount:(NSString *)account password:(NSString *)password completion:(void (^)(ZYUserVerifyResult *result,int retcode,NSString *errDescription))handler  ;

/***
 * 忘记密码：设置新密码
 * @param account ：手机号或邮箱
 * @param password ：新设置的密码
 * @param verifyCode ：验证码
 * @param handler callback(retcode,errDescription)
 */
-(void) forgetPwdAndSetNewWithAccount:(NSString *)account password:(NSString *)password verifyCode:(NSString *)verifyCode completion:(callbackRetcode) handler ;


/***
 * 修改绑定账号（修改手机或邮箱）-获取验证码
 * 注：用于修改或绑定手机号/邮箱号。
 * @param account ：要修改/绑定的手机号或邮箱号
 * @param password ：用户密码
 * @param handler callback(isPhone,smsRemain,retcode,errDescription)
 */
-(void) getModifyAccountVerifyWithAccount:(NSString *)account password:(NSString *)password completion:(void (^)(ZYUserVerifyResult *result,int retcode,NSString *errDescription)) handler;

/***
 * 修改（或绑定）手机号或邮箱号
 * @param account ：要修改的手机号或邮箱号
 * @param password ：用户密码
 * @param verifyCode ：验证码
 * @param handler callback(retcode,errDescription)
 */
-(void) modifyAccountWithAccount:(NSString *)account password:(NSString *)password verifyCode:(NSString *)verifyCode completion:(void (^)(int retcode,NSString *errDescription))handler;



/**
 * 解除微信公众号绑定（解除后无法收到微信通知）
 * @param handler callback(retcode,errDescription)
 */
-(void) wechatRemovePublic:(callbackRetcode)handler;

/**
 * 注销用户
 * 注：注销用户后，需要重新注册才可登录使用
 * @param password 密码
 * @param handler callback(retcode,errDescription)
 */
-(void) deleteUserWithPassword:(NSString *)password completion:(callbackRetcode)handler;




/**一级用户授权给二级用户
 注：设备未购买任何套餐，设备的二级用户最高9个，购买套餐后，最高99个。
 * @param keyhash ：指定设备keyhash
 * @param account ：被授权的二级用户的账号(已注册的手机或邮箱)
 * @param authority ：用户控制权限，详见AboutEntity.h中的AuthorityEntity定义
 * @param remark ：备注
 * @param handler callback(authUser,retcode,errDescription)
 */
-(void) authorizeUserWithKeyhash:(NSString *)keyhash account:(NSString *)account authority:(AuthorityEntity *)authority remark:(NSString *)remark completion:(void (^)(ZYAuthUser *authUser,int retcode,NSString *errDescription))handler;


/**
 * 一级用户修改二级用户权限
 * @param keyhash ：指定设备keyhash
 * @param authUserId ：被授权的二级用户userId，这里不用account
 * @param authority ：用户控制权限，用户控制权限，详见AboutEntity.h中的AuthorityEntity定义
 * @param remark ：备注
 * @param handler callback(retcode,errDescription)
 */
-(void) modifyAuthUserWithKeyhash:(NSString *)keyhash authUserId:(NSString *)authUserId authority:(AuthorityEntity *)authority remark:(NSString *)remark completion:(callbackRetcode)handler;


/***
 * 一级用户解授权二级用户 （解授权后，二级用户失去对设备的权限）
 * @param keyhash ：指定设备keyhash
 * @param authUserId ：被授权的二级用户userId，这里不用account
 * @param handler callback(retcode,errDescription)
 */
-(void) unAuthorizeUserWithKeyhash:(NSString *)keyhash authUserId:(NSString *)authUserId completion:(callbackRetcode)handler;

/**
 * 获取设备所属的用户列表（包括二级用户，临时用户）
 * @param keyhash 指定设备
 * @param handler callback(authUserArray,tempUserArray,retcode,errDescription)
 */
-(void) getUserListWithKeyhash:(NSString *)keyhash completion:(void (^)(NSMutableArray *authUsers,NSMutableArray *tempUsers,int retcode,NSString *errDescription))handler;

/***
 * 转移设备管理员权限给指定用户
 * 注：1.管理员才可以转移设备，转移设备后该用户失去管理员权限，设备下的所有二级用户、临时用户均被删除，设备新管理员是指定的用户。
 *@param loginPwd 转移设备管理员权限需要用户登录密码
 * @param keyhash 设备
 * @param account 转移给指定用户（为已注册的手机或邮箱）
 * @param handler callback(retcode,errDescription)
 */
-(void) moveDevToUserWithPassword:(NSString *)loginPwd keyhash:(NSString *)keyhash account:(NSString *)account completion:(callbackRetcode)handler;


/**
 * 获取所有的设备套餐信息
 * @param handler callback(devChargeInfoArray,retcode,errDescription)
 */
-(void) getDevChargeInfos:(void (^)(NSMutableArray *chargeInfos,int retcode,NSString *errDescription))handler;

/**
 * 获取设备已购套餐信息
 * @param keyhash 指定设备
 * @param handler callback(purchasedChargeInfoDic,retcode,errDescription)
 */
-(void) getDevChargePurchasedInfosWithKeyhash:(NSString *)keyhash completion:(void (^)(NSMutableDictionary *purchasedInfoDic,int retcode,NSString *errDescription))handler;

/***
 * 获取设备套餐的价格
 * @param chargeId 指定套餐Id
 * @param handler callback(chargeInfo-（不含devTypeId字段）,retcode,errDescription)
 */
-(void) getDevChargePayPriceWithChargeId:(NSString *)chargeId completion:(void (^)(ChargeInfoDev *chargeInfo,int retcode,NSString *errDescription))handler;

/**
 * 提交购买设备套餐结果（下单、支付的流程在商城类APP及其后台自己实现，购买成功后再调用本接口，本SDK不涉及金钱）
 * @param keyhash 指定设备
 * @param chargeId 指定套餐Id
 * @param handler callback(retcode,errDescription)
 */
-(void) buyDevChargeNoWithKeyhash:(NSString *)keyhash chargeId:(NSString *)chargeId completion:(callbackRetcode)handler;


/**
 * 删除已购买的设备套餐
 * 注：如果用户购买设备录套餐后想要换套餐，要先删除套餐，再购买新套餐
 * @param keyhash 指定设备
 * @param chargeMark 套餐类型标志，1历史记录套餐，2操控套餐
 * @param handler callback(retcode,errDescription)
 */
-(void) deleteDevChargewithKeyhash:(NSString *)keyhash chargeMark:(ZYDevChargeType) chargeMark completion:(callbackRetcode)handler;

/**
 * 为设备设置月推邮箱
 * 注：1、月推邮箱是需要购买了设备套餐才可以设置；2、只有设备的管理员可以设置月推邮箱；3、筑云后台于每月1号0点0分发出月推送，月推邮箱接收到的内容是设备上个月产生的历史记录（包括：设备异常状态、设备操控记录、设备绑定分享记录）
 * 月推邮箱账号默认包含设备管理员的邮箱。
 * @param keyhash 指定设备
 * @param email 月推邮箱，可以设置两个，邮箱之间用英文符号分号‘;’分隔开，形如“cxm@qq.com;cxm2@qq.com”
 * @param handler callback(retcode,errDescription)
 */
-(void) setDevPushEmailWithKeyhash:(NSString *)keyhash email:(NSString *)email completion:(callbackRetcode)handler;

/**
 * 获取短信套餐信息
 * 注：用户可以在不登录的情况下充值。
 * @param handler callback(SMSChargeInfoArray,retcode,errDescription)
 */
-(void) getSMSChargeInfos:(void (^)(NSMutableArray *smsChargeInfos,int retcode,NSString *errDescription))handler;

/**
 * 获取短信套餐的价格
 * @param chargeId 指定套餐Id
 * @param handler callback(SMSChargeInfo,retcode,errDescription)
 */
-(void) getSMSChargePayPriceWithChargeId:(NSString *)chargeId completion:(void (^)(ChargeInfoSMS *smsChargeInfo,int retcode,NSString *errDescription))handler;

/***
 *  提交购买短信套餐结果（下单、支付的流程在商城类APP及其后台自己实现，购买成功后再调用本接口，本SDK不涉及金钱）
 * @param phoneNum 手机号（已注册的手机号）
 * @param chargeId 指定套餐Id
 * @param handler callback(retcode,errDescription)
 */
-(void) buySMSChargeNoWithPhone:(NSString *)phoneNum chargeId:(NSString *)chargeId completion:(callbackRetcode)handler;







@end
