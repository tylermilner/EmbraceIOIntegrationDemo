# EmbraceIOIntegrationDemo
Sample project showing that integration of the embrace.io SDK causes the XCUITest target to fail.

## The Problem
After integrating the embrace.io SDK, the XCUITest target will fail to run with the following error:
```
Test target <target_name> encountered an error (Early unexpected exit, operation never finished bootstrapping - no restart will be attempted)
```

![UI test target fails to run](/Images/test_target_fail_small.png)

## The Fix
The embrace.io SDK pod needs to be added to the UI testing target in order for the UI test target to run successfully. When integrating the embrace.io SDK with a project that has an XCUITest target, your podfile should look something like this:
```ruby
# Uncomment the next line to define a global platform for your project
# platform :ios, '9.0'

target 'EmbraceIOIntegrationDemo' do
  # Comment the next line if you're not using Swift and don't want to use dynamic frameworks
  use_frameworks!

  # Pods for EmbraceIOIntegrationDemo
  pod 'EmbraceIO'

  target 'EmbraceIOIntegrationDemoTests' do
    inherit! :search_paths
    # Pods for testing
  end

  target 'EmbraceIOIntegrationDemoUITests' do
    inherit! :search_paths
    # Pods for testing
    pod 'EmbraceIO'
  end

end
```

## Steps to Reproduce

### From the branches in this repo
1. Checkout the `testsWorking` branch and open `EmbraceIOIntegrationDemo.xcworkspace`.
2. Run all tests using the shortcut `CMD` + `U`. Observe all test targets complete successfully.
3. Checkout the `testsFailing` (or `master` branch). Observe that the `EmbraceIOIntegrationDemoUITests` target fails to launch.

### From scratch
1. Create a new project.
![Create a new project](/Images/create_project.png)

2. Podify the project by running the following command. Then open `<project_name>.xcworkspace`.
```
pod init
```

3. Run all tests using the shortcut `CMD` + `U`. Observe all test targets complete successfully.
![Tests passing](/Images/test_target_success.png)

4. Add the embrace.io pod to your podfile and then run `pod install`.
```ruby
# Uncomment the next line to define a global platform for your project
# platform :ios, '9.0'

target 'EmbraceIOIntegrationDemo' do
  # Comment the next line if you're not using Swift and don't want to use dynamic frameworks
  use_frameworks!

  # Pods for EmbraceIOIntegrationDemo
  pod 'EmbraceIO'

  target 'EmbraceIOIntegrationDemoTests' do
    inherit! :search_paths
    # Pods for testing
  end

  target 'EmbraceIOIntegrationDemoUITests' do
    inherit! :search_paths
    # Pods for testing
  end

end
```

5. Run all tests using the shortcut `CMD` + `U`. Observe that the UI testing target fails to run.
![Tests failing](/Images/test_target_fail.png)
