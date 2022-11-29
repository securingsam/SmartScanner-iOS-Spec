Pod::Spec.new do |s|
    s.name                  = "SmartScannerSDK"
    s.version               = "1.0.0"
    s.summary               = "SAM Seamless Network - SmartScanner SDK."
    s.homepage              = "https://securingsam.com"
    s.license               = "Private"
    s.author                = { "SAM Seamless Network" => "info@securingsam.com" }
    s.source                = { :git => "git@github.com:securingsam/SmartScanner-Ios.git", :tag => s.version }

    s.platform              = :ios, "14.0"
    s.swift_version         = "5.0"
    s.requires_arc          = true

    s.source_files          = 'Pod/Classes'
    s.resources             = 'Pod/Assets/*'

    s.static_framework      = true

    s.frameworks            = 'UIKit', 'SwiftUI', 'CoreMedia', 'Network', 'Combine'
    s.module_name           = 'SAM_SmartScannerSDK'
end
