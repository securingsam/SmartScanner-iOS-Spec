Pod::Spec.new do |spec|
    spec.name                  = "SmartScannerSDK"
    spec.version               = "1.0.0"
    spec.summary               = "SAM Seamless Network - SmartScanner SDK."
    spec.description           = "..."
    spec.homepage              = "https://securingsam.com"
    spec.license               = { :type => 'Private', :text => 'SAM Seamless Network private license.' }
    spec.author                = { "SAM Seamless Network" => "info@securingsam.com" }
    spec.source                = { :git => 'git@github.com:securingsam/SmartScanner-iOS-Spec.git', :branch => "main" }

    # Dependency frameworks
    spec.frameworks            = 'SystemConfiguration', 'SystemServices', 'Network', 'CoreLocation', 'CoreMedia', 'Combine', 'CommonCrypto', 'AppIntents'

    # Supported deployment targets
    spec.platform              = :ios
    spec.ios.deployment_target = "14.0"
    spec.swift_version         = "5.3"

    # Published binaries
    spec.vendored_frameworks        = "SmartScannerSDK.xcframework"
  end