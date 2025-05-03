char* createMessage() {
  char* buffer = (char*)malloc(20);  // dynamically allocate memory
  if (buffer != nullptr) {
    strcpy(buffer, "hello world");
  }
  return buffer;  // return raw pointer (non-const here, but you can use const)
}

const char* getMessage() {
  return createMessage();  // wrap it with const
}

void setup() {
  Serial.begin(9600);
  const char* msg = getMessage();

  // Uncommenting the following line will give a compiler error
  // msg[0] = 'H';  // ❌ Not allowed: msg is const

  // Cast away const (⚠️ only safe here because we know the memory is heap)
  char* writable = (char*)msg;
  writable[0] = 'H';  // ✅ Legal and safe here

  Serial.println(writable);  // Output: Hello world

  // This results in a warning!
  // warning: invalid conversion from ‘const char*’ to ‘char*’ [-fpermissive]
  char* uncasted_message = getMessage();

  free(writable);  // always free what you malloc!
}

void loop() {
  // nothing to do here
}
