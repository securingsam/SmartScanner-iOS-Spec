// swift-tools-version:5.6
import PackageDescription

let package = Package(
    name: "SmartScannerSDK",
    platforms: [.iOS(.v14)],
    products: [
        .library(
            name: "SmartScannerSDK",
            targets: ["SmartScannerSDK"]
        )
    ],
    targets: [
        .binaryTarget(
            name: "SmartScannerSDK",
            path: "SmartScannerSDK.xcframework"
        )
    ]
)
