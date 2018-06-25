Pod::Spec.new do |s|
  s.name         = 'SPSDKPay'
  s.version      = '1.1.2'
  s.summary      = 'Supay iOS SDK'
  s.description  = <<-DESC
                   移动应用支付接口。
                   开发者不再需要编写冗长的代码，简单几步就可以使你的应用获得支付功能。
                   让你的移动应用接入支付像大厦接入电力一样简单，方便，和温暖。
                   支持微信支付，支付宝支付。
                   DESC
  s.homepage     = 'https://github.com/supaytech/superpay-ios-sdk'
  s.license      = 'COMMERCIAL'
  s.author       = { 'Afon Weng' => 'lm.zou@rechengit.com' }
  s.platform     = :ios, '8.0'
  s.source       = { :git => 'https://github.com/supaytech/superpay-ios-sdk.git', :tag => s.version }
  s.requires_arc = true
  s.default_subspec = 'Core', 'Alipay', 'Wx', 'UnionPay'

  s.subspec 'Core' do |core|
    core.source_files = 'lib/*.h'
    core.public_header_files = 'lib/*.h'
    core.vendored_libraries = 'lib/*.a'
    core.resource = 'lib/*.bundle'
    core.frameworks = 'CFNetwork', 'SystemConfiguration', 'Security', 'CoreLocation'
    core.ios.library = 'c++', 'stdc++', 'z'
    core.xcconfig = { 'OTHER_LDFLAGS' => '-ObjC' }
  end

  s.subspec 'Alipay' do |ss|
    ss.vendored_libraries = 'lib/Channels/Alipay/*.a'
    ss.vendored_frameworks = 'lib/Channels/Alipay/*.framework'
    ss.resource = 'lib/Channels/Alipay/*.bundle'
    ss.frameworks = 'CoreMotion', 'CoreTelephony'
    ss.dependency 'SPSDKPay/Core'
  end

  s.subspec 'Wx' do |ss|
    ss.source_files = 'lib/Channels/Wx/*.h'
    ss.vendored_libraries = 'lib/Channels/Wx/*.a'
    ss.dependency 'SPSDKPay/Core'
  end

  s.subspec 'UnionPay' do |ss|
    ss.source_files = 'lib/Channels/UnionPay/*.h'
    ss.vendored_libraries = 'lib/Channels/UnionPay/*.a'
    ss.dependency 'SPSDKPay/Core'
  end
end
