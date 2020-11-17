//
//  ZYBaseSDK.h
//  ZYIOTSDK
//
//  Created by ZYIT_cxm on 2018/11/29.
//  Copyright © 2018年 ZYIT All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AboutZYEntity.h"
#import "ZYIOTClientStateDelegate.h"
#import "IOTOnlineDelegate.h"
 
@protocol ZYSDKLoginDelegate  //SDK状态回调接口
//-(void)sdkLoginExpire:(NSString *)errDescription;//SDK Login状态失效，重新init后可重试恢复Login状态
-(void)sdkLoginSuccess;//SDK init 成功
-(void)sdkLoginFailure:(int)retcode err:(NSString *)errDescription ;//SDK init 失败（SDK内API无法正常使用）
@end

@protocol MyEventResponseDelegate  //Event相关回调接口
/**
 接收到一个event消息，此时接收方是APP（APP可以解析本Event属性值进行处理）。ZY平台主动下发event时source无值。
 @param event event消息封装，包含设备属性名、属性值等
 @param source 发出Event的一方，指的是设备keyhash或null(平台)。如设备状态变更时发送Event通知APP，此时source是设备keyhash.
 */
- (void)onEventForAPP:(MyEventData *)event fromSource:(NSString *)source isRead:(BOOL)isRead readState:(BOOL)readState;

/**
 接收到一个event消息，此时接收方是app的直连子设备（APP解析本Event属性值后下发给指定的子设备-childDevKeyhash）。监听到本event需要再发送给对应的子设备。（子设备分为网关下挂子设备、APP下挂子设备，不直接使用IOT的设备是子设备，对于APP来说子设备是APP直连子设备比如蓝牙设备 ）。如现用户的设备列表有一个蓝牙子设备C，此时接收到本Event[attrName=statew,type=1,attrValue1=2]且childDevKeyhash=C，那么APP通过蓝牙为C设备设置statew值为2。
 ZY平台主动下发event时source无值。
 @param event event消息封装，包含设备属性名、属性值等
 @param source event的发起方（设备ID或null）
 @param childDevKeyhash  子设备ID（表示需要将这个值再发给对应的子设备）
 */
- (void)onEventForChildDev:(MyEventData *)event fromSource:(NSString *)source toChildDevKeyhash:(NSString *)childDevKeyhash isRead:(BOOL)isRead readState:(BOOL)readState;

/**app直连子设备登录和退出登录结果.
 loginResult：登录或退出的结果，true表示成功。
 *isLogin：true表示本次是登录回调，false是退出登录回调。
 *childDevKeyhash：app直连子设备的keyhash
 *childDevType：app直连子设备的类型（全小写字母），比如bluetooth。
 **/
- (void)onEventForChildDevLoginOrOut:(BOOL)loginResult isLogin:(BOOL)isLogin childDevKeyhash:(NSString *)childDevKeyhash childDevType:(NSString *)childDevType;

/**发送event后，接收event失败。
 eventId：发送的消息ID（可自己指定封装，或随机数生成）*/
-(void) onEventFailureWithEventId:(int32_t)eventId;

/**发送event后，将会收到这个回调。
 *isSuccess：true表示已经成功发送到服务器，false表示发送到服务器失败；
 eventId：发送的消息ID（可自己指定封装，或随机数生成），用于对应发送的event*/
-(void) onEventSyncResponseWithStatus:(BOOL)isSuccess eventId:(int32_t)eventId;
@end

/**SDK基类，通用SDK接口定义，具体使用请使用ZYOpenAccountSDK和ZYAccountSDK。*/
@interface ZYBaseSDK : NSObject
@property (nonatomic) long long lastTimestamp;//second

+(instancetype) getBaseInstance;

/**
 初始化IOT Client端
 */
-(void)initIOTClient;

/**
修改IOT Client的一些设置
 @param servers IOT服务器IP或域名
 @param clientStateDelegate IOT Client 状态变化监听
 @param hexTypeSize 语音文件时单片分片的最大数据长度
 */
-(void)setIOTClientWithServer:(NSString *)servers stateDelegate:(id<ZYIOTClientStateDelegate>)clientStateDelegate hexTypeSize:(int)hexTypeSize;

/**
 设置接收或发送语音文件分片的数据内容长度
 @param hexTypeSize max Frame length
 */
-(void)setIOTHexTypeSize:(int)hexTypeSize;
/**
 获取接收或发送语音文件分片的数据内容长度 max Frame length
 */
-(int ) getIOTHexTypeSize;
/**
 IOT服务器
 @param servers 设置IOT服务器IP或域名（若有多个，用英文符号分号隔开）
 */
-(void)setIOTServer:(NSString *)servers;

/**
 设置监听IOTClient的状态监听
 @param clientStateDelegate IOT client状态变化中监听代理
 */
-(void)setIOTClientStateDelegate:(id<ZYIOTClientStateDelegate>) clientStateDelegate;

/**
 修改IOT Client状态state:1(start or resume); 2(pause); -1(stop).
 注：不需要与设备进行设备通信时，pause或stop可以降低通信损耗。
    发送event时状态需要是已经start才可正常通信。
 @param state change iot client state
 */
-(void)toASyncStartOrStopIOTClient:(int)state;

/**增加代理监听event消息的发送和接收情况
 @param eventResponseDelegate 代理监听event消息情况
 */
-(void)addZYEventResponseDelegate:(id<MyEventResponseDelegate>)eventResponseDelegate;

/**
  移除指定监听
 @param eventResponseDelegate 代理监听event消息情况
 */
-(void)removeZYEventResponseDelegate:(id<MyEventResponseDelegate>)eventResponseDelegate;

/**
 增加代理监听IOT Client的在线和异常离线的状态变化
 @param onlineDelegate IOTOnlineDelegate
 */
-(void)addZYClientOnlineDelegate:(id<IOTOnlineDelegate>)onlineDelegate;

/**
 移除指定IOTOnlineDelegate代理
 @param onlineDelegate IOTOnlineDelegate
 */
-(void)removeZYClientOnlineDelegate:(id<IOTOnlineDelegate>)onlineDelegate;

/**
 获取本机的keyhash
 @return app phone keyhash
 */
-(NSString *) getPhoneKeyhash;

/** 获取IOT Client的状态。-1:stop, 1:start, 2:pause ,3:resume。 */
-(int) getIOTClientState;

/**
 APP母设备发送int值的event（如APP直接控制设备时）
 @param eventId 指定的消息ID
 @param attrName 属性名
 @param valueInt int的属性值
 @param targetKeyhash 发送event到指定设备
 @return 返回eventId数值则成功，其余描述失败
 */
-(NSString *)sendEventIntFromApp:(int32_t)eventId attrName:(NSString *)attrName valueInt:(int32_t)valueInt targetKeyhash:(NSString *)targetKeyhash;

/**
 APP母设备发送string值的event （如APP直接控制设备时）
 @param eventId 指定的消息ID
 @param attrName 属性名
 @param valueStr string的属性值
 @param targetKeyhash 发送event到指定设备
 @return 返回eventId数值则成功，其余描述失败
 */
-(NSString *)sendEventStrFromApp:(int32_t)eventId attrName:(NSString *)attrName valueStr:(NSString *)valueStr targetKeyhash:(NSString *)targetKeyhash;

/** APP母设备发送（NSData）hex值的event——如语音文件 （如APP直接控制设备时）
 @param eventId 指定的消息ID
 @param attrName 属性名
 @param valueHexBytes 发送NSData的属性值(如语音文件)
 @param targetKeyhash 发送event到指定设备
 @return 返回含eventId数值则成功，其余描述失败
 */
-(NSString *)sendEventHexFromApp:(int32_t)eventId attrName:(NSString *)attrName valueHexBytes:(NSData *)valueHexBytes targetKeyhash:(NSString *)targetKeyhash;

/** childDev发送int值的event（如子设备直接控制其它设备时）
 @param eventId 指定的消息ID
 @param attrName 属性名
 @param valueInt int的属性值
 @param targetKeyhash 发送event到指定设备
 @param childDevKeyhash 子设备ID
 @return 返回eventId数值则成功，其余描述失败
 */
-(NSString *)sendEventIntFromChildDev :(int32_t)eventId attrName:(NSString *)attrName valueInt:(int32_t)valueInt targetKeyhash:(NSString *)targetKeyhash childDevKeyhash:(NSString *)childDevKeyhash;

/** childDev发送string值的event（如子设备直接控制其它设备时）
 @param eventId 指定的消息ID
 @param attrName 属性名
 @param valueStr string的属性值
 @param targetKeyhash 发送event到指定设备
 @param childDevKeyhash 子设备ID
 @return 返回eventId数值则成功，其余描述失败
 */
-(NSString *)sendEventStrFromChildDev:(int32_t)eventId attrName:(NSString *)attrName valueStr:(NSString *)valueStr targetKeyhash:(NSString *)targetKeyhash childDevKeyhash:(NSString *)childDevKeyhash;

/** childDev发送（NSData）hex值的event-语音文件 (如子设备直接控制其它设备时）
 @param eventId 指定的消息ID
 @param attrName 属性名
 @param valueHexBytes NSData的属性值
 @param targetKeyhash 发送event到指定设备
 @param childDevKeyhash 子设备ID
 @return 返回含eventId数值则成功，其余描述失败
 */
-(NSString *)sendEventHexFromChildDev:(int32_t)eventId attrName:(NSString *)attrName valueHexBytes:(NSData *)valueHexBytes targetKeyhash:(NSString *)targetKeyhash childDevKeyhash:(NSString *)childDevKeyhash;

/**
   APP母设备发送event（如APP直接控制设备时）
 @param eventId 指定的消息ID
 @param type 属性值类型：1(string) ,2(int), 3(string+int), 4(hex). 指定了属性值类型，则对应的属性值字段才有效（如type=1，valueStr有效）
 @param attrName 属性名
 @param valueStr string类型的属性值
 @param valueInt int类型的属性值
 @param valueHexBytes NSData类型的属性值
 @param targetKeyhash 指定的设备
 @return 返回含eventId数值则成功，其余描述失败
 */
-(NSString *)sendEventFromApp:(int)eventId attrType:(int)type attrName:(NSString *)attrName valueStr:(NSString *)valueStr valueInt:(int)valueInt valueHex:(NSData *)valueHexBytes target:(NSString *)targetKeyhash;

/**
 APP直连子设备发送event（如APP直接控制设备时），比如蓝牙设备会先连接手机，然后调用子设备登录成功后，再使用本接口将蓝牙设备当前状态通过event上传到服务器保存。
 @param eventId 指定的消息ID
 @param type 属性值类型：1(string) ,2(int), 3(string+int), 4(hex). 指定了属性值类型，则对应的属性值字段才有效（如type=1，valueStr有效）
 @param attrName 属性名
 @param valueStr string类型的属性值
 @param valueInt int类型的属性值
 @param valueHexBytes NSData类型的属性值
 @param targetKeyhash 指定的设备
 @param childDevKeyhash 子设备ID
 @return 返回含eventId数值则成功，其余描述失败
 */
-(NSString *)sendEventFromChildDev:(int)eventId attrType:(int)type attrName:(NSString *)attrName valueStr:(NSString *)valueStr valueInt:(int)valueInt valueHex:(NSData *)valueHexBytes target:(NSString *)targetKeyhash childDevKeyhash:(NSString *)childDevKeyhash;

/**
APP直连子设备登录
 @param childDevType 子设备的类型，指的是蓝牙设备等app直连设备类型，目前支持bluetooth（小写字母）
 @param childDevKeyhash 连接app成功的子设备ID
 @return  返回eventId数值则成功，其余描述失败
 */
-(NSString *)childDevLogin:(NSString * )childDevType childDevKeyhash:(NSString *)childDevKeyhash;

/**
 APP直连子设备退出登录
 @param childDevType 子设备的类型，指的是蓝牙设备等app直连设备类型，目前支持bluetooth（小写字母）
 @param childDevKeyhash 与app连接断开的子设备ID
 @return  返回eventId数值则成功，其余描述失败
 */
-(NSString *)childDevLogout:(NSString * )childDevType childDevKeyhash:(NSString *)childDevKeyhash;


/**
 读取指定设备的指定属性值。
 注意：读取hex类型的属性时应该attrName=指定attrName，type=1，返回的是hex文件ID列表(形如objectId_timestamp,objectId_timestamp)。然后将文件ID列表中的objectId值作为attrName(此时type=4)依次发送event去获取文件内容。
 @param targetKeyhash  指定设备ID
 @param attrName 指定属性名
 @param attrType 属性值类型
 @return 返回eventId数值则成功，其余描述失败
 */
-(NSString *)sendEventToReadDevAttrFromAPP:(NSString *)targetKeyhash attrName:(NSString *)attrName attrType:(int32_t)attrType;
/**
 读取指定APP直连子设备的指定属性值。
 注意：读取hex类型的属性时应该attrName=指定attrName，type=1，返回的是hex文件ID列表(形如objectId_timestamp,objectId_timestamp)。然后将文件ID列表中的objectId值作为attrName(此时type=4)依次发送event去获取文件内容。
 @param targetKeyhash  指定读取的设备ID
 @param childDevKeyhash 再将得到的值发回给指定子设备
 @param attrName 指定属性名
 @param attrType 属性值类型
 @return 返回eventId数值则成功，其余描述失败
 */
-(NSString *)sendEventToReadDevAttrFromChildDev:(NSString *)targetKeyhash childDevKeyhash:(NSString *)childDevKeyhash  attrName:(NSString *)attrName attrType:(int32_t)attrType;


/**
 连接筑云ZOT服务器URL
 */
-(NSString *)getZotUrlBaseStr;

/**
 连接筑云DNS服务器URL
 */
-(NSString *)getDNSUrlBaseStr;
/**
 获取DNSKey
 *DNSKey是访问筑云dns服务器的身份令牌，是由筑云分配给开发者的，请提前申请
 */
-(NSString *) getDNSKey;
/**
 设置DNSKey
 *DNSKey标识了APP对应服务器DNS信息，获取DNS信息前需要先设置DNSKey
 */
-(void)setDNSKey:(NSString *)dnsKey;
/**
 设置DNS服务器域名或IP地址（只能设置一个域名或IP）
 *@param dnsDomain 修改DNS API连接的服务器域名或IP
 */
-(void)setHttpDNSServerDomain:(NSString *)dnsDomain;

/**
 @param tenantId 筑云提供的一个数字标识
 */
-(void)setTenantId:(int) tenantId ;

/** ZOT服务器， 只能一个域名或IP
 @param domain 修改ZOT API连接的服务器域名或IP
 */
-(void)setZotDomain:(NSString *) domain ;

/**
 @param port 修改API连接服务器时使用的http端口号
 */
-(void) setZotPort:(int)port ;

/**
 true is login ok.如果login=NO则需要重新initSDK，以保证sdk正常使用
 @return is init sdk correct
 */
-(BOOL) isSDKLogin;

/**设置监听sdk的zot token是否过期*/
-(void)setSDKLoginDelegate:(id<ZYSDKLoginDelegate>)zyLoginDelegate;
/**
 获取zotToken

 @return zot token
 */
-(NSString *) getZotToken;

/**
 设置zotToken
 @param zotToken zot token
 */
-(void) setZotToken:(NSString *)zotToken;

/**
获取zotRefreshToken
 @return zot refreshToken
 */
-(NSString *) getZotRefreshToken;

/**
 设置zotRefreshToken
 @param zotRefreshToken  zot refreshToken
 */
-(void) setZotRefreshToken:(NSString *)zotRefreshToken;

/**校验是否过期，retcode返回码是203，表示token无效或过期*/
//-(void)checkRetcodeExpire:(int)retcode;
/**
 获取属性值（全部属性）
 @param keyhash keyhash
 @param handler callback
 */
-(void) getDevAttrListWithKeyhash:(NSString *)keyhash completion:(void (^)(DeviceInfoEntity *dev,int retcode ,NSString *errDescription)) handler;



/**
 获取属性值列表（不包含全局属性，全局属性与普通属性的区别是全局属性值由厂家设置，不允许用户修改，且没有时间戳值）
 @param keyhash device
 @param handler callback
 */
-(void) getDevAttrListForNoGlobalWithKeyhash:(NSString *)keyhash  completion:(void (^)(DeviceInfoEntity *dev,int retcode ,NSString *errDescription)) handler;


/**
 设置属性
 @param keyhash 设备
 @param name attrNames (多个属性时用英文符号“;”分号分隔，分隔后的属性名数量与属性值分隔后的属性值数量要一致)
 @param value attrValues（多个属性时用英文符号“;”分隔）
 @param handler  callback
 */
-(void) setDevAttrsWithKeyhash:(NSString *)keyhash attrName:(NSString *)name attrValue:(NSString *)value completion:(void (^)(int retcode ,NSString *errDescription)) handler;

/**
 *设备绑定摄像头、为摄像头设置摄像头信息
 *注：设备只能绑定一个摄像头信息
 *@param keyhash 设备
 *@param cameraInfo 萤石摄像头信息（用户accessToken、cameraId摄像头Id、默认密码(验证码)、摄像头当前密码）。请确保accessToken对应的用户对这个camera有权限
 *@param  handler callback
 */
-(void)devBindCameraWithkeyahsh:(NSString *)keyhash cameraInfo:(DeviceCameraInfo *)cameraInfo completion:(void(^)(int retcode,NSString *errDescription)) handler;

/**
 *设备删除绑定的摄像头
 *@param keyhash 设备
 *@param  handler callback
 */
-(void)devDeleteCameraWithkeyahsh:(NSString *)keyhash completion:(void(^)(int retcode,NSString *errDescription)) handler;


/**
 设备重置，同时将清除所有与用户的绑定关系
 @param keyhash device
 @param handler callback
 */
-(void) devResetDevWithKeyhash:(NSString *) keyhash completion:(void (^)(int retcode ,NSString *errDescription)) handler;



/**获取历史记录
 参数：
 keyhash
 timestamp1：起始时间戳，以秒为单位
 timestamp2：结束时间戳，以秒为单位
 limit：log返回条数限制，如果limit=0，不做限制
 注：1.如果timestamp1和timestamp2都为0，说明查找所有数据；如果timestamp1>=0，timestamp2>0，说明查找timestamp1和timestamp2之间的数据;要求timestamp1和timestamp2都大等于0，且timestamp1<=timestamp2;
 2.获取的历史记录是与自己相关的历史记录，不是所有用户的历史记录，这与zot2.0不同。
 handler:callback array:DeviceLogEntity
 */
-(void) getDevLogsWithKeyhash:(NSString *)keyhash timestamp1:(NSString *)timestamp1 timestamp2:(NSString *)timestamp2 limit:(NSString *)limit completion:(void (^)(NSMutableArray *devLogs,int retcode ,NSString *errDescription)) handler ;


/**
 绑定设备
 @param keyhash 设备ID，在设备二维码上可见
 @param devTypeId 指定设备类型，在设备二维码上可见
 @param handler callback
 */
-(void) bindDevWithKeyhash:(NSString *) keyhash devTypeId:(NSString *)devTypeId completion:(void (^)( int retcode ,NSString *errDescription)) handler;



/**
 删除设备。若是管理员删除设备，设备的二级用户都将同步删除。
 @param keyhash device
 @param handler callback
 */
-(void) deleteDeviceWithKeyhash:(NSString *)keyhash completion:(void (^)( int retcode ,NSString *errDescription)) handler ;


/**
 获取用户下的设备列表（不含属性值）
 @param handler callback array:DeviceInfoEntity
 */
-(void) getDevListWithCompletion:(void (^)(NSMutableArray *devs,int retcode ,NSString *errDescription)) handler;


/**
 获取用户下带部分属性的设备列表
 设备包含的属性值有：camera@zot、online@zot、devname@zot、dev_head_protrait@zot、expire_time@zot。分别表示绑定的摄像头信息、在线状态、设备名称、设备头像图片名、设备过期时间。
 @param handler callback array:DeviceInfoEntity
 */
-(void) getDevListWithSomeAttrsWithCompletion:(void (^)(NSMutableArray *devs,int retcode ,NSString *errDescription)) handler;

/**增加临时用户分享
 参数：
 keyhash：设备标识
 authority：临时分享权限，json格式
 remark：备注
 注：1.分享临时用户成功后，生成二维码，二维码为网址，扫描二维码跳转到网页，临时用户可以直接控制设备。二维码包含参数包括tenantId，tempShareId，devTypeId。
 2.需要log，不需要统计。删除临时用户也一样。
 3.authority，临时分享权限，包含两种，一种是时段控制，一种是时段单次控制。格式为json格式。时段控制格式如下：{"type": "0","time": "1234500000-1345600000","shareTime": "1234500000"}；时段单次控制格式如下：{"type": "1","time": "1234500000-2345600000","controlTime": "12434500000","shareTime": "1234500000"}。
    type为0表示时段控制，为1表示时段单次控制。
    time包含起始和结束时间戳，中间用-隔开，精确到秒。
    controlTime为操控时间，只针对时段单次控制有效，如果control_time为空，表示未操控，为时间戳表示操控时间。
    shareTime为临时用户分享时间。
    所有字段都为String格式。
    (时间戳单位：second)
 @param handler callback
 */
-(void)shareTempUserWithKeyhash:(NSString *)keyhash authority:(AuthorityTempEntity *)authority remark:(NSString *)remark completion:(void (^)(NSString *tempShareId,int retcode ,NSString *errDescription)) handler ;

/**
 编辑临时用户权限
 参数:
 tempShareId：临时分享Id
 authority：临时分享权限，json格式
 remark：备注
 handler: callback
 */
-(void)modifyTempUserWithTempShareId:(NSString*)tempShareId authority:(AuthorityTempEntity *)authority remark:(NSString*)remark completion:(void (^)( int retcode ,NSString *errDescription)) handler;

/**
 删除临时用户
 参数：
 tempShareId：临时分享Id
 */
-(void)deleteTempUserWithTempShareId:(NSString*)tempShareId completion:(void (^)(int retcode ,NSString *errDescription)) handler;

/**
 设置设备推送开关
 参数：
 keyhash
 可选参数：(只传入有效值，不设置则置空)
 pushSwitch：推送开关
 emailSwitch：邮箱推送开关
 wechatSwitch：微信推送开关
 */
-(void) setDevPushSwitchWithKeyhash:(NSString*)keyhash pushSwitch:(NSString*)pushSwitch emailSwitch:(NSString*)emailSwitch wechatSwitch:(NSString*)wechatSwitch completion:(void (^)( int retcode ,NSString *errDescription)) handler;

/**
 获取设备触发器列表
 @param handler  callback array:DeviceTrigger
 注：设备触发器的创建、修改、删除都需要厂家权限，普通用户不能操作。普通用户只能查看触发器列表。
 */
-(void)getDevTriggerListWithCompletion:(void (^)(NSMutableArray *devTriggers,int retcode ,NSString *errDescription)) handler;


/**获取设备触发器开关
 @param keyhash  device
 @param triggerId  触发器Id
 @param handler callback
 */
-(void) getDevTriggerSwitchWithKeyhash:(NSString*)keyhash triggerId:(NSString*)triggerId completion:(void (^)(NSString *triggerId,NSString *triggerSwitch,int retcode ,NSString *errDescription)) handler;

/**
 设置触发器开关
 @param keyhash device id
 @param triggerId  trigger id
 @param triggerSwitch 触发器开关  true为开，false为关
 @param handler callback
 */
-(void) setDevTriggerSwitchWithKeyhash:(NSString*)keyhash  triggerId:(NSString*)triggerId triggerSwitch:(BOOL)triggerSwitch completion:(void (^)(int retcode ,NSString *errDescription)) handler;

/**
 获取设备自定义触发器列表
 @param keyhash device id
 @param handler callback array:DeviceCustomerTrigger
 */
-(void) getDevCustomTriggerListWithKeyhash:(NSString*)keyhash completion:(void (^)(NSMutableArray *devCustomerTriggers,int retcode ,NSString *errDescription)) handler;


/**
 用户增加一个设备自定义触发器
 @param keyhash device id
 @param attrName  attrName
 @param condition attrvalue的触发条件，json格式数据，包含operation，threshold。operation：触发条件，包括：>，<，>=，<=，==，!=，contains，equals。threshold：阈值。
 @param timeLimit 时间限制，json格式数据，包含字段说明：type：操控类型，0表示全时访问，无需time和week；1表示时段访问，无需week；2表示定期访问。time表示操控时间，如果是时段访问，内容为起始-结束时间戳(单位：second)，中间用-分割；如果是定期访问，内容为当天时间的起始秒-结束秒（24小时制 ，如上午8:00对应的秒数是28800），中间用-分割。week表示星期，1-7分别表示周一到周日，如：137表示周一周三周日。形如：{"type":"2","time":"12345-23456","week":"127"}
 @param status 触发状态，是否可触发，true是，false否
 @param remark  备注
 @param handler  callback
 */
-(void) addDevCustomTriggerWithKeyhash:(NSString*)keyhash attrName:(NSString*)attrName condition:(NSString*)condition timeLimit:(AuthorityEntityDevTimeLimit*)timeLimit status:(BOOL)status remark:(NSString*)remark completion:(void (^)(NSString *triggerId,int retcode ,NSString *errDescription)) handler;

/**
 修改一个自定义触发器
 @param triggerId triggerId
 @param keyhash  device id
 @param attrName attr name
 @param condition attrvalue的触发条件 ,JSON格式
 @param timeLimit 时间限制,json格式
 @param status 触发状态，是否可触发，true是，false否
 @param remark 备注
 @param handler callback
 */
-(void) modifyDevCustomTriggerWithTriggerId:(NSString*)triggerId keyhash:(NSString*)keyhash attrName:(NSString*)attrName condition:(NSString*)condition timeLimit:(AuthorityEntityDevTimeLimit*)timeLimit status:(BOOL)status remark:(NSString*)remark completion:(void (^)(int retcode ,NSString *errDescription)) handler;

/**删除一个自定义触发器
 @param triggerId trigger id
 @param handler callback
 */
-(void) deleteDevCustomTriggerWithTriggerId:(NSString*)triggerId completion:(void (^)(int retcode ,NSString *errDescription)) handler;

/** 获取场景列表 
 @param handler  callback array:DeviceSceneInfo
 */
-(void) getSceneListWithCompletion:(void (^)(NSMutableArray *devSceneInfos,int retcode ,NSString *errDescription)) handler ;

/**
 增加一个场景
 @param sceneName  scene name
 @param sceneType 场景类型  0：定时任务  1：设备联动。注：场景类型创建后不能修改
 @param remark 备注
 @param handler callback
 */
-(void) addSceneWithSceneName:(NSString*)sceneName sceneType:(ZYSceneType)sceneType remark:(NSString*)remark completion:(void (^)(NSString *sceneId,int retcode ,NSString *errDescription)) handler;

/**修改一个场景
 @param sceneId scenen id
 @param sceneName scenne name
 @param remark 备注
 @param handler callback
 */
-(void) modifySceneWithSceneId:(NSString*)sceneId sceneName:(NSString*)sceneName remark:(NSString*)remark completion:(void (^)( int retcode ,NSString *errDescription)) handler;

/**
 删除一个场景。注：会将场景相关定时任务或设备联动都删除
 @param sceneId scenen id.场景Id
 @param handler callback
 */
-(void) deleteSceneWithScenenId:(NSString*)sceneId completion:(void (^)(int retcode ,NSString *errDescription)) handler;

/**
 获取单个场景的详细信息，含任务列表：定时任务列表或联动任务列表
 @param sceneId scenen id
 @param handler callback
 */
-(void) getSceneInfoWithSceneId:(NSString*)sceneId completion:(void (^)(DeviceSceneInfo *scene,int retcode ,NSString *errDescription)) handler;

/**
 获取设备下的定时任务列表
 @param keyhash device
 @param handler callback array:DeviceTimedTask
 */
-(void) getDevTimedTaskWithKeyhash:(NSString*)keyhash completion:(void (^)(NSMutableArray *devTimedTasks,int retcode ,NSString *errDescription)) handler;


/**增加一条定时任务
 (时间戳单位：second)
 定时任务时间有两种，一种是定期单次任务，一种是周重复任务。定期单次任务是指定具体时间，为年月日时分的时间戳，周重复任务是指定周几的几时几分，最小精确到分钟。
 @param keyhash device
 @param time 任务触发时间，如果是定期单次，如北京时间2017/11/7 10:26:00，存储为1510021560。如果是周重复任务，time为小时分钟转换成秒数，小时分钟随系统时间（24小时制），如上午8点对应的秒数是28800。
 @param attrName 属性名
 @param attrValue 属性值
 @param repeat 任务重复，如果是定期单次任务，repeat为空。如果是周重复任务，repeat才有效。repeat值为1,2,3,4,5,6,7，分别代表周一到周日，此处多天时必须用英文逗号隔开。如值为"1,3,6"表示"周一 周三 周六"。
 @param remark 备注
 @param sceneId 加入指定场景，不加入到场景则此值可为空
 @param handler callback
 */
-(void)addDevTimedTaskWithKeyhash:(NSString*)keyhash time:(NSString*)time attrName:(NSString*)attrName attrValue:(NSString*)attrValue repeat:(NSString*)repeat remark:(NSString*)remark sceneId:(NSString*)sceneId completion:(void (^)(NSString *timedTaskId,int retcode ,NSString *errDescription)) handler;

/**修改一条定时任务
 @param timedTaskId timedTaskId
 @param keyhash device
 @param time 任务触发时间，如果是定期单次，如北京时间2017/11/7 10:26:00（时间戳单位：秒），存储为1510021560。如果是周重复任务，time为小时分钟转换成秒数，小时分钟随系统时间（24小时制 ，如上午8:00对应的秒数是28800）。
 @param attrName 属性名
 @param attrValue 属性值
 @param repeat 任务重复，如果是定期单次任务，repeat为空。如果是周重复任务，repeat才有效。repeat值为1,2,3,4,5,6,7，分别代表周一到周日，此处多天时必须用英文逗号隔开。如值为"1,3,6"表示"周一 周三 周六"。
 @param remark 备注
 @param sceneId 加入指定场景，不加入到场景则此值可为空
 @param handler callback
 */
-(void) modifyDevTimedTaskWithTimedTaskId:(NSString*)timedTaskId keyhash:(NSString*)keyhash time:(NSString*)time attrName:(NSString*)attrName attrValue:(NSString*)attrValue repeat:(NSString*)repeat remark:(NSString*)remark sceneId:(NSString*)sceneId completion:(void (^)( int retcode ,NSString *errDescription)) handler;

/**
 删除一条定时任务
 @param timedTaskId timedTask Id
 @param handler callback
 */
-(void)deleteDevTimedTaskWithTimedTaskId:(NSString*)timedTaskId completion:(void (^)(int retcode ,NSString *errDescription)) handler;

/**  获取该用户下的设备联动任务列表
 @param handler callback array:DeviceLinkage
 */
-(void) getDevLinkageListWithCompletion:(void (^)(NSMutableArray *devLinkages,int retcode ,NSString *errDescription))handler;

/**
 增加一条设备联动
 @param keyhash  联动设备1（主动联动设备，触发设备）
 @param attrName 联动设备1的属性名
 @param condition 设备联动条件, 触发条件——属性值条件判断。json格式数据，包含operation，threshold。operation：触发条件，包括：>，<，>=，<=，==，!=，contains，equals。threshold：阈值。
 形如：{"operation":">","threshold":"20"}
 @param keyhash2 联动设备2（被动联动设备-执行设备，可以和触发设备keyhash相同）
 @param attrName2 联动设备2的属性名
 @param attrValue2 联动设备2下发的属性值
 @param timeLimit 联动时间限制，在该时段内才有效。若为空，则表示全时段有效。json格式数据：type：操控类型，0表示全时访问，无需time和week；1表示时段访问，无需week；2表示定期访问。time表示操控时间，如果是时段访问，内容为起始-结束时间戳(单位：second)，中间用-分割；如果是定期访问，内容为当天时间的起始秒-结束秒（24小时制 ，如上午8:00对应的秒数是28800），中间用-分割。week表示星期，1-7分别表示周一到周日，如：137表示周一周三周日。 形如：{"type":"2","time":"12345-23456","week":"127"}
 @param remark 备注
 @param sceneId 加入指定的场景，
 @param handler callback
 */
-(void)addDevLinkageWithKeyhash:(NSString*)keyhash attrName:(NSString*)attrName condition:(NSString*)condition keyhash2:(NSString*)keyhash2 attrName2:(NSString*)attrName2 attrValue2:(NSString*)attrValue2 timeLimit:(AuthorityEntityDevTimeLimit*)timeLimit remark:(NSString*)remark sceneId:(NSString*)sceneId completion:(void (^)(NSString *linkageId,int retcode ,NSString *errDescription)) handler;

/**
 修改一条设备联动
 @param linkageId devLinkage id
 @param keyhash  联动设备1（主动联动设备，触发设备）
 @param attrName 联动设备1的属性名
 @param condition 设备联动条件，json格式内容，详见增加联动任务API中condition字段参数的描述。
 @param keyhash2 联动设备2（被动联动设备-执行设备，可以和keyhash相同）
 @param attrName2 联动设备2的属性名
 @param attrValue2 联动设备2下发的属性值
 @param timeLimit 联动时间限制，在该时段内才有效。若为空，则表示全时段有效。json格式内容，详见增加联动任务API中timeLimit字段参数的描述。
 @param remark 备注
 @param sceneId 加入指定的场景
 @param handler callback
 */
-(void)modifyDevLinkageWithLinkageId:(NSString*)linkageId keyhash:(NSString*)keyhash attrName:(NSString*)attrName condition:(NSString*)condition keyhash2:(NSString*)keyhash2 attrName2:(NSString*)attrName2 attrValue2:(NSString*)attrValue2 timeLimit:(AuthorityEntityDevTimeLimit*)timeLimit remark:(NSString*)remark sceneId:(NSString*)sceneId completion:(void (^)( int retcode ,NSString *errDescription)) handler;

/**
 删除一条设备联动
 @param linkageId dev linkage id
 @param handler callback
 */
-(void)deleteDevLinkageWithLinkageId:(NSString*)linkageId completion:(void (^)(int retcode ,NSString *errDescription)) handler;

/**
 用户反馈
 @param content 反馈内容
 @param contact 联系方式
 @param handler  callback
 */
-(void) userFeedbackWithContent:(NSString*)content contact:(NSString*)contact completion:(void (^)(int retcode ,NSString *errDescription)) handler;


/**获取属性操作对应内容
 @param devTypeId 设备类型Id
 @param handler  callback array:DevAttrOperation
 */
-(void)getDevAttrOperationWithDevTypeId:(NSString*)devTypeId completion:(void (^)(NSMutableArray *attrOperations,int retcode ,NSString *errDescription)) handler;

/**
 获取公众号二维码 ,扫描二维码可绑定公众号，然后可以接收到微信推送 
 @param handler callback->url
 */
-(void)getWechatPublicQRCodeWithCompletion:(void (^)(NSString *wechatURLStr,int retcode ,NSString *errDescription)) handler;



/**
 * 根据语言获取所有消息类型
 * @param language ：指定返回的语言内容，形如“en”
 * @param handler  callback(msgTypeList,retcode ,errDescription)
 */
-(void) getMessageTypeListWithLanguage:(NSString *)language completion:(void (^)(NSMutableArray *msgTypes,int retcode,NSString *errDescription)) handler;

/** 获取消息列表-根据语言和设备类型获取
 * @param timestamp 截止时间戳（单位：毫秒），在这个时间之前的消息不获取；如果要获取所有消息，timestamp设为0；
 * @param devTypeId ：指定的设备类型对应的消息，有多个设备类型时需要使用英文分号将设备类型分隔开，形如“1;2;3”；
 * @param language ：指定返回的语言内容，形如“en”
 * @param handler callback(msgList,deleteMsgList,retcode ,errDescription)
 */
-(void) getMessageListWithLanguage:(NSString *) language timestamp:(long long)timestamp devTypeId:(NSString *)devTypeId completion:(void (^)(NSMutableArray *msgs,NSMutableArray *deleteMsgs,int retcode,NSString *errDescription)) handler;

/***
 * 获取服务器的DNS信息
 * 注：1、调用此接口前请先调用SDK接口setDNSKey设置DNSKey之后才可以成功获取APP对应的服务器DNS信息
 2、DNSKey是由筑云分配给APP开发者的，请提前申请
 * @param handler callback(httpDNSInfoList,retcode ,errDescription)
 */
-(void) getHttpDNSInfosWithCompletion:(void (^)(NSMutableArray *httpDNSInfos,int retcode,NSString *errDescription)) handler;

@end

