
node
{
stage('SCM'){
checkout([$class: 'GitSCM', branches: [[name: '*/master']], doGenerateSubmoduleConfigurations: false, extensions: [], submoduleCfg: [], userRemoteConfigs: [[url: 'https://github.com/kunalborker/text-rpg']]])
}

stage('Build') {
sh label: '', script: '''#!/bin/bash
make'''
}

stage('SonarQube analysis') {
bat label: 'SonarQube', script: 'C:\\sonar-scanner\\bin\\bin\\sonar-scanner.bat -Dsonar.host.url=http://localhost:9000 "-Dsonar.projectBaseDir=C:\\Program Files (x86)\\Jenkins\\workspace\\Text RPG"'
}

stage('Upload'){
step([$class: 'NexusArtifactUploader', artifacts: [[artifactId: 'text-rpg', classifier: '', file: 'game.exe', type: 'exe']], credentialsId: 'nexus', groupId: 'CPP', nexusUrl: 'localhost:8081', nexusVersion: 'nexus3', protocol: 'http', repository: 'CPP', version: '1.0.0'])
}
}
