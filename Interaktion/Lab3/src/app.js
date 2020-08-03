// helper function to find the container by short name
const container=function(containerName){
  return document.body.querySelector("#container-"+containerName);
};   
// the View containers will not all be visible at the same time.
// Various screens will show different Views
const screens = {
  home: ["header","home"],
  search: ["header", "sidebar", "search"],
  overview: ["header", "overview"],
  details:  ["header", "sidebar", "details"],
  printout: ["header", "printout"]
}; 
class General_state_controller{
  constructor(){
  }

  show = function(screenName) {
    if(window.matchMedia("(max-width: 800px)").matches){
      document.querySelector("#container-search").style = "grid-column: 1/6;";
      document.querySelector("#container-details").style = "grid-column: 1/6;";
    }
  
    ["header", "home", "overview", "search", "sidebar", "details", "printout"]
      .forEach(containerName => container(containerName).style.display="none");
  
    // now we show all the Views used by the indicated screen
    screens[screenName]
      .forEach(containerName => container(containerName).style.display = "grid"); 
  
    if(window.matchMedia("(max-width: 800px)").matches){
      document.querySelector("#container-sidebar").style.display = "none";
    }
  }; 

  searchDishes = function() {
    this.show("search");
  }
}
// switching between screens 


const IMAGEKEY = "https://spoonacular.com/recipeImages/";

window.onload = function () {
  //We instantiate our model 
  const model = new DinnerModel();
  const gsc = new General_state_controller();

  const hv = new HomeView(container("home"), gsc);
  const ov = new OverviewView(container("overview"), model);
  const sv = new SearchView(container("search"), model);
  const dv = new DetailsView(container("details"), model);
  const pv = new PrintoutView(container("printout"), model);
  const sbv = new SidebarView(container("sidebar"), model);

  model.setNumberOfGuests(this.localStorage.getItem('guests'));

  let p1 = model.getDish(595476).then((data) => {model.addDishToMenu(data);});
  let p2 = model.getDish(133769).then((data) => {model.addDishToMenu(data);});
  let p3 = model.getDish(420420).then((data) => {model.addDishToMenu(data);});
  let p4 = model.getDish(1).then((data) => {model.addDishToMenu(data);});

  //let p5 = model.getAllDishes(null,"meatballs").then((data) => {sv.render(data);});

  Promise.all([p1,p2,p3,p4]).then((data) => {
    ov.render(); 
    dv.render(); 
    pv.render(); 
    sbv.render();
    hv.render();
    gsc.show("home"); 
  }) 
  sbv.afterRender();
  sv.afterRender();
  hv.afterRender();
}; 