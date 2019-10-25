using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace Lab2_wb.Controllers
{
    public class StudentController : Controller
    {
        // GET: Student
        public string Index()
        {
            return "Showing you all the students.";
        }

        public string Show (int? id)
        {
            if (!id.HasValue)
            {
                return "Dati un id";
            }

            return ("id: " + id + " name: numeStudent " + "group: 344");
        }

        public string Create (int? id, string name, int? group)
        {
            if (!id.HasValue)
            {
                return "Dati un id";
            }

            if (name == null)
            {
                return "Dati un nume";
            }

            if (!group.HasValue)
            {
                return "Dati o grupa";
            }

            return "Created "  + ("id: " + id + " " + "name: " + name + " " + "group: " + group);
        } 

        public string Update (int? id, string name, int? group)
        {
            if (!id.HasValue)
            {
                return "Dati un id";
            }

            if (name == null)
            {
                return "Dati un nume";
            }

            if (!group.HasValue)
            {
                return "Dati o grupa";
            }

            return "Updated to " + ("id: " + id + " " + "name: " + name + " " + "group: " + group);
        }

        public string Delete (int? id)
        {
            if (!id.HasValue)
            {
                return "Dati un id";
            }

            return "Deleted student " + id;
        } 
    }
}