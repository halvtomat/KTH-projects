class SearchView {
  constructor(container, model) {
    this.container = container;
    this.model = model;
    this.model.addObserver(this);
  }

  search() {
    let type = this.container.querySelector("#categorySelect").value;
    let query = this.container.querySelector("#searchBar").value;
    this.model.getAllDishes(type, query).then((data) => {
      for(let i = 0; i < 5; i++){
        this.container.querySelector("#image"+(i+1)).src = IMAGEKEY+data[i].image;
        this.container.querySelector("#image_text"+(i+1)).innerHTML = data[i].title;
      }
    });
  }
  
  update(){

  }

  afterRender() {
    this.container.querySelector("#searchSubmitBtn").addEventListener("click", () => {
      this.search(this);
    });
  }
}
