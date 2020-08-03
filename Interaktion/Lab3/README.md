# Interaction Programing - Lab 2
This project contains the startup code for Lab 2, which focuses on the model. For more details on how to complete the 
assignment follow the instructions on the 
[course website](https://kth.instructure.com/courses/19629/assignments/100300).

## Git Setup instructions
* You will need a KTH Gits account. You can access it by logging in with your KTH.se account credentials. The login button is placed to the right in the navigation bar. Click [here](https://intra.kth.se/en/it/programvara-o-system/system/kth-github/kth-github-1.500062) for more information about your KTH Gits account.
Follow these steps in detail to be able to work with GitHub from your computer
    * Generate a new ssh key: 
    https://help.github.com/en/articles/generating-a-new-ssh-key-and-adding-it-to-the-ssh-agent
    * Add the ssh key to GitHub: 
    https://help.github.com/en/articles/adding-a-new-ssh-key-to-your-github-account
* Fork the startup code ([KTH Gits](https://gits-15.sys.kth.se/iprog/dinnerplanner-html/tree/lab1-with-tests)) - 
the button is in the upper right corner
* Clone your new repository to the computer (either using GitHub Desktop App or terminal)
    * If you’re using the command line you will have to type “git clone <ssh_url>”
    * Find the ssh_url here in your forked repository on GitHub
    * Remember to make sure you’re cloning with SSH, and not with HTTPS. 

## Configuring the API
This application uses the [spoonacular API](https://rapidapi.com/spoonacular/api/recipe-food-nutrition). In order for 
the application to work it needs to have access to that api. In order to grant the application access to the api you 
must rename *apiConfig.js.template* to *apiConfig.js* in */src/model/*. Then fill in the ENDPOINT and API_KEY 
constants with the endpoint for making API fetches and your spoontacular api key. Once you've done so, these 
constants can be used in */src/model/dinnerModel.js*.  

**IMPORTANT:** Do not name the file anything other than *apiConfig.js*, otherwise your api key might end up on 
github. If you do rename the file to something other than *apiConfig.js*, then be sure to include that file in the 
[gitignore](https://git-scm.com/docs/gitignore)!

## Testing
Open `index.html` in the browser and tests should run automatically

## What's in this repo
TODO: describe the view files here.
* [index.html](/index.html) - open to run the tests. 
* [src/model/dinnerModel.js](/src/model/dinnerModel.js) - write code here. This is a skeleton for the model of the 
application, but it does not yet support the functionality needed (number of guests, selected dishes, et.c.). It also 
contains a first dummy hardcoded "database" to use as test data.
* [src/model/dinnerModel.test.js](/src/model/dinnerModel.test.js) - tests for the model. You do not need to modify 
these, but study how they are written. You might be asked to write more tests in the future. In your opinion, do 
these tests cover the most important areas, or would you have written them differently? 

* [src/app.js](/src/app.js) - this is the overall code of the application. It is responsible for initial setup of the 
app (when the page loads for the first time). You will find it more relevant when you start working with views in 
future labs.
* [images/](/images) - folder contains some pictures you can use for your dishes.



