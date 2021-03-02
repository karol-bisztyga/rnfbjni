import { StatusBar } from 'expo-status-bar';
import React from 'react';
import { StyleSheet, Text, View } from 'react-native';

export default function App() {
  const fullText = "1234567890qwertyuiop";
  const nativeTrimTest = global.trimModule?.nativeTrim(fullText) ?? "not working :( :( :(";
  console.log("nativeTrimTest", nativeTrimTest);
  return (
    <View style={styles.container}>
      <Text>full text: {fullText}</Text>
      <Text>natively trimmed text: {nativeTrimTest}</Text>
      <StatusBar style="auto" />
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: '#fff',
    alignItems: 'center',
    justifyContent: 'center',
  },
});
