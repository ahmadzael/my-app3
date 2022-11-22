import ExpenseItem from "./ExpenseItem";
import Card from "../UI/Card";
import './ExpenseItem.css'

function Expenses(props){

    return(
        <Card className="expenses">
        <ExpenseItem 
          title={props.item[0].title}
          amount={props.item[0].amount}
          date={props.item[0].date}
        ></ExpenseItem>
        <ExpenseItem 
          title={props.item[1].title}
          amount={props.item[1].amount}
          date={props.item[1].date}
        ></ExpenseItem>
        <ExpenseItem 
          title={props.item[1].title}
          amount={props.item[1].amount}
          date={props.item[1].date}
        ></ExpenseItem>
        <ExpenseItem 
          title={props.item[1].title}
          amount={props.item[1].amount}
          date={props.item[1].date}
        ></ExpenseItem>
      </Card>
    );
}
export default Expenses;  