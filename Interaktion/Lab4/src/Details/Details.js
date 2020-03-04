import React, { Component } from "react";
import { withRouter } from 'react-router-dom';
import modelInstance from "../data/DinnerModel";
import "./Details.css";

class Details extends Component {
    constructor(props) {
        super(props);

        this.state = {
            status: "LOADING"
        }
        this.pathname = this.props.location.pathname;
        this.dishId = this.pathname.substr(6, this.pathname.length - 6)
    }

    componentDidMount(){
        this.getDish();
    }
    getDish = () => {
        modelInstance
            .getDish(this.dishId)
            .then(dish => {
                this.setState({
                    status: "LOADED",
                    dish: dish
                })
            })
            .catch(() => {
                this.setState({
                    status: "ERROR"
                })
            })
    }
    
    render() {
        let img = null;
        let header = null;
        console.log(this.state.dish);
        switch(this.state.status){
            case "LOADING":
                img = <em>Loading...</em>;
                header=<h1 className="Details_header">Loading...</h1>;
                break;

            case "LOADED":
                img = <img 
                    className="details_image" 
                    src={"https://spoonacular.com/recipeImages/"+this.state.dish.id+"-556x370.jpg"} 
                    alt={this.state.dish.alt}>
                </img>;
                header=<h1 className="details_header">{this.state.dish.title}</h1>;
                break;

            default:
                img = <em>BIG ERROR</em>;
                break;
        }
        return (
            <div className="details">
                {header}
                {img}
                <div className="details_text">{lorem1}</div>
                <h1 className="preparation">Preparation</h1>
                <div className="preparation_text">{lorem2}</div>
                <button className="button" id="backbtn">Back to search</button>
                <div className="ingredient_box">
                    <div className="ingredient_box_top">box</div>
                    <div className="ingredient_box_middle">box</div>
                    <div className="ingredient_box_bottom">
                        <button className="button" id="addbtn">
                            Add to Menu
                        </button>
                    </div>
                </div>

            </div>
        );

    }
}
const lorem1 = "Lorem ipsum dolor sit amet consectetur adipisicing elit. Sed ab similique, dolor impedit corporis pariatur aperiam veritatis nostrum minima! Asperiores quas ad sed esse laborum ullam earum quae obcaecati maiores corporis molestiae accusamus, adipisci dolorum est magni non provident in.";
const lorem2 = "Lorem ipsum dolor sit,amet consectetur adipisicing elit. Fugit nobis non vel vero pariatur ab odio quo error molestiae? Rerum, eligendi. Maxime, voluptates labore. Dolores repudiandae, quibusdam dignissimos exercitationem perferendis provident voluptatibus eum vel nemo nulla numquam consectetur nostrum nesciunt qui tenetur ab magni ducimus quo ratione. Dicta quod quidem animi magni dolor earum qui beatae natus, voluptatum minus quis incidunt provident assumenda velit perspiciatis dolore odit neque ducimus? Quidem illum labore adipisci libero excepturi, recusandae cumque dolore consectetur, velit ex voluptas deserunt eos architecto in enim inventore nostrum maxime! Totam quo, provident ipsum at optio quae, expedita esse corporis cum nihil magni libero similique, eos labore! Aliquid, officiis? Nisi delectus cumque praesentium eius ducimus accusamus, tempore corrupti odit laborum. Corrupti voluptatem ullam itaque labore velit autem provident ex cum laborum nobis rerum nihil, vitae quisquam qui illo voluptas maxime dolore neque sunt sit doloremque repellendus placeat. Dolor necessitatibus eos totam quis omnis rerum, labore ipsam debitis hic accusantium! Adipisci consequatur odit architecto repellendus, eos nostrum obcaecati minus nisi nam doloribus commodi laborum ullam quod quas ea dignissimos dolorem sit, soluta mollitia nihil dolorum provident. Nulla adipisci, architecto maxime facere debitis officia exercitationem cum alias nisi necessitatibus odio incidunt et!";
export default withRouter(Details);
