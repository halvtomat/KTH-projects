class DetailsView {
    constructor(container, model) {
        this.container = container;
        this.model = model;
    }
    render() {
        
        this.container.querySelector("#ingredients_box_top").innerHTML = "Ingredients for " + this.model.getNumberOfGuests() + " people";

        let data = this.model.getFullMenu()[3];
        this.container.querySelector("#details_image").src = data.image;
        this.container.querySelector("#details_header").innerHTML = data.title;
        this.container.querySelector("#preparation_text").innerHTML = data.instructions;
        this.container.querySelector("#ingredients_box_middle").innerHTML = "";
        for(let i = 0; i < data.extendedIngredients.length; i++){
          let newIngredient = document.createElement("ingredient");
          newIngredient.id = "ingredient" + i;
          newIngredient.className = "ingredient";
          newIngredient.innerHTML = data.extendedIngredients[i].amount +" "+ data.extendedIngredients[i].unit +" "+ data.extendedIngredients[i].name;
          document.querySelector("#ingredients_box_middle").appendChild(newIngredient);
        }
    }
    
    afterRender() {
    }
  }
  