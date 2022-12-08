// swift-tools-version:5.6
import PackageDescription

let package = Package(
    name: "SmartScannerSDK",
    platforms: [.iOS(.v14)],
    swiftLanguageVersions: [.v5],
    products: [
        .library(
            name: "SmartScannerSDK",
            targets: ["SmartScannerSDK"]
        )
    ],
    targets: [
        .binaryTarget(
            name: "SmartScannerSDK",
            path: "1.0.0/SmartScannerSDK.xcframework"
        )
    ]
)
